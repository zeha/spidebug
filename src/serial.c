#include "common.h"
#include <stdint.h>
#include <stdbool.h>
#include "unit.h"
#include "../shared/generated.h"

enum STATE {
    state_listening,
    state_rx_address,
    state_rx_command,
    state_rx_length,
    state_rx_data,
    state_tx_begin,
    state_tx_address,
    state_tx_command,
    state_tx_length,
    state_tx_data,
    state_tx_finishing
};

enum STATE serial_state;
timer_ticks_t serial_state_since;
//enum ERRORS last_command_error;

void func_command_set(void);
void func_command_ping(void);
void func_command_produce(void);

static enum SERIAL_COMMANDS command;

int serial_messages_received = 0;
int serial_messages_processed = 0;

uint8_t serial_rx_buffer[SERIAL_BUFFER_SIZE];
uint8_t* serial_rx_pointer;
static uint8_t rx_length;
static uint8_t rx_received_data_length;

uint8_t serial_tx_buffer[SERIAL_BUFFER_SIZE];
uint8_t serial_rx_error_too_much_data = 0;
static uint8_t* tx_pointer = 0;
static uint8_t* tx_pointer_start = 0;
static uint8_t tx_address;
static uint8_t tx_command;
static uint8_t tx_length;
static unsigned char tx_rombuffer_pong[] = "PONG";

// group control id = 1
#define DEVICE_TYPE 1
// device_id
#define DEVICE_ID 1
#define DEVICE_ID_ALL 0

#define ADDRESS_Z 0
#define SYNC_BYTE 'U'

#ifdef __PICC18__
// should select 115200 (actually 117647 at 32mhz)
#define BAUDRATE_COEFFICIENT 16

#define BUS_DIRECTION LATC5
#define BUS_DIRECTION_TRIS TRISC5
#define BUS_DIRECTION_RECEIVE 1
#define BUS_DIRECTION_TRANSMIT 0

#define RX_REG        RCREG
#define TX_REG        TXREG

#define SOFTWARE_ECHO_CONTROL
#define SIMPLEX_UART

#elif __XC32

// Fpb = 80MHz, Baudrate = 115200:
// In[2]:= Solve[115200==80000000/(4*C+1),C] // N
// Out[2]= {{C->173.361}}
#define BAUDRATE_COEFFICIENT 173

#define RX_REG        U2RXREG
#define TX_REG        U2TXREG

#define BUS_DIRECTION LATFbits.LATF12
#define BUS_DIRECTION_TRIS TRISFbits.TRISF12
#define BUS_DIRECTION_RECEIVE 0
#define BUS_DIRECTION_TRANSMIT 1

#define SOFTWARE_ECHO_CONTROL

#else
#error "No serial defines for this CPU"

#endif

void serial_init(void) {
    serial_rx_pointer = serial_rx_buffer;

    serial_state = state_listening;
    serial_state_since = 0;
#ifdef SOFTWARE_ECHO_CONTROL
    BUS_DIRECTION = BUS_DIRECTION_RECEIVE;
    BUS_DIRECTION_TRIS = TRIS_OUTPUT;
#endif

#ifdef __PICC18__
    TRISC6 = 0;
    TRISC7 = 1;
    IPR1bits.RCIP = 0;
    IPR1bits.TXIP = 0;
    OpenUSART(
        USART_RX_INT_ON &
        USART_ASYNCH_MODE &
        USART_EIGHT_BIT &
        USART_CONT_RX &
        USART_BRGH_HIGH,
        BAUDRATE_COEFFICIENT);
    RCIE = 1;
    TXIE = 0;
    TXEN = 0;
#elif __XC32
    U2BRG = BAUDRATE_COEFFICIENT;
    // Configure TX/RX/RTS pins, BRGH=1
    U2MODE = (1 << _U2MODE_UEN0_POSITION) | _U2MODE_RTSMD_MASK | _U2MODE_BRGH_MASK;
    U2STA = _U2STA_URXEN_MASK | _U2STA_UTXEN_MASK;

    // Enable UART module
    U2MODEbits.ON = 1;

    uint32_t int_priority = 2;
    uint32_t sub_prio = 0;

    // Clear interrupt enable flags
    IEC0CLR = _IEC1_U2RXIE_MASK | _IEC1_U2TXIE_MASK | _IEC1_U2EIE_MASK;
    // Clear interrupt flags
    IFS0CLR = _IFS1_U2RXIF_MASK | _IFS1_U2TXIF_MASK | _IFS1_U2EIF_MASK;

    // Configure Priority and Subpriority
    IPC8CLR = _IPC8_U2IP_MASK | _IPC8_U2IS_MASK;
    IPC8SET = int_priority << _IPC8_U2IP_POSITION;
    IPC8SET = sub_prio << _IPC8_U2IS_POSITION;

    // Set interrupt enable flags
    IEC1SET = _IEC1_U2RXIE_MASK | _IEC1_U2TXIE_MASK;

#else
#error "No serial_init implementation for this CPU"
#endif
}

int pending_command = 0;

void serial_handle_rx_bus(void) {
    uint8_t byte = RX_REG;

    switch (serial_state) {
    case state_listening:
        if (byte != SYNC_BYTE)
            return;

        serial_state = state_rx_address;
        serial_state_since = 0;
        break;

    case state_rx_address:
        if ((byte & 0x80) == 0) {
            // most likely we saw "UU" in a data stream
            serial_state = state_listening;
            serial_state_since = 0;
            return;
        }
        if (((byte & 0x1c) >> 3) != DEVICE_TYPE) {
            // not for us (device type mismatch)
            serial_state = state_listening;
            serial_state_since = 0;
            return;
        }
        uint8_t to = (byte & 0x3);
        if (to != DEVICE_ID_ALL && to != unit_id) {
            // not for us (device id mismatch)
            serial_state = state_listening;
            serial_state_since = 0;
            return;
        }
        serial_messages_received++;

        serial_rx_pointer = serial_rx_buffer;
        *serial_rx_pointer = '\0';
        rx_length = 0;
        rx_received_data_length = 0;

        serial_state = state_rx_command;
        serial_state_since = 0;
        break;

    case state_rx_command:
        if (byte == SYNC_BYTE) {
            serial_state = state_listening;
            serial_state_since = 0;
            break;
        }

        command = byte;

        serial_state = state_rx_length;
        serial_state_since = 0;
        break;

    case state_rx_length:
        if (byte == SYNC_BYTE) {
            serial_state = state_listening;
            serial_state_since = 0;
            break;
        }

        rx_length = byte;

        serial_state = state_rx_data;
        serial_state_since = 0;
        if (rx_received_data_length > sizeof(serial_rx_buffer)-1) {
            ++serial_rx_error_too_much_data;
            serial_state = state_listening;
            serial_state_since = 0;
        }
        break;

    case state_rx_data:
        if (command == command_firmware_update) {
            // sends way too much data for our ram
            // TODO: implement me
            // don't forget SYNC_BYTE doubling!
            rx_received_data_length++;
        } else {
            /*
             * SYNC Byte doubling is disabled for now, as the remote can't do it
             * at this time.
            if (*rx_pointer == SYNC_BYTE) {
                // handle second byte of sync byte doubling
                if (byte == SYNC_BYTE) {
                    rx_pointer++;
                    *rx_pointer = '\0';
                } else {
                    // abort receive, invalid byte sequence
                    serial_state = state_listening;
                    break;
                }
            } else {
                if (byte == SYNC_BYTE) {
                    // first byte of sync byte doubling, save and wait for next byte
                    *rx_pointer = SYNC_BYTE;
                    break;
                }
            }
             */

            rx_received_data_length++;

            *serial_rx_pointer = byte;

            if (rx_received_data_length == rx_length) {
                // done
                serial_state = state_listening;
                serial_state_since = 0;
                serial_messages_processed++;

                // can only have commands here that DO NOT REPLY.
                switch (command) {
                case command_set: func_command_set(); break;
                default:
                    pending_command = command;
                    break;
                }

                // NOTE: do not set serial_state here, as func_command_*
                // might have changed it already (think tx())
            } else {
                serial_rx_pointer++;
                *serial_rx_pointer = '\0';
            }
        }
        break;
    default:
        // TX
        break;
    }
}

void serial_handle_rx_raw(void) {
    uint8_t byte = RX_REG;
    rx_received_data_length++;

    if (serial_rx_pointer >= serial_rx_buffer+sizeof(serial_rx_buffer)) {
        serial_rx_pointer = serial_rx_buffer;
    }

    *serial_rx_pointer = byte;
    serial_rx_pointer++;
    *serial_rx_pointer = '\0';
}

bool serial_handle_tx(void) {
    if (serial_state == state_listening) {
        return false;
    }

    if (tx_pointer == 0 || serial_state == state_tx_finishing) {
        // done transmitting or error state, enter receiving mode
#ifdef SIMPLEX_UART
        TXIE = 0;
        TXEN = 0;
        RCIE = 1;
        CREN = 1;
#endif
        serial_state = state_listening;
        serial_state_since = 0;
#ifdef SOFTWARE_ECHO_CONTROL
        BUS_DIRECTION = BUS_DIRECTION_RECEIVE;
#endif
        return false;
    }

    switch (serial_state) {

    case state_tx_begin:
        serial_state = state_tx_address;
        serial_state_since = 0;
        TX_REG = 'U';
        break;

    case state_tx_address:
        serial_state = state_tx_command;
        serial_state_since = 0;
        TX_REG = tx_address;
        break;

    case state_tx_command:
        serial_state = state_tx_length;
        serial_state_since = 0;
        TX_REG = tx_command;
        break;

    case state_tx_length:
        serial_state = state_tx_data;
        serial_state_since = 0;
        TX_REG = tx_length;
        break;

    case state_tx_data:
    {
        char *p = tx_pointer++;
        if (tx_pointer >= (tx_pointer_start+tx_length)) {
            serial_state = state_tx_finishing;
            serial_state_since = 0;
            // don't disable TXIE here, but do it only after we're done sending
            // (= when we re-enter the ISR)
        }
        TX_REG = *p;
        break;
    }

    default:
        return false;
    };

    return true;
}

void serial_begin_tx(uint8_t address, uint8_t command, uint8_t length, uint8_t *buffer) {
#ifdef SIMPLEX_UART
    TXIE = 0;
    RCIE = 0;
    CREN = 0;
#endif

    tx_address = address | 0xC0;
    tx_command = command;
    tx_length = length;
    tx_pointer_start = buffer;
    tx_pointer = buffer;

#ifdef SOFTWARE_ECHO_CONTROL
    BUS_DIRECTION = BUS_DIRECTION_TRANSMIT;
#endif
    serial_state = state_tx_begin;
    serial_state_since = 0;
#ifdef SIMPLEX_UART
    TXIE = 1;
    TXEN = 1;
#endif
    serial_handle_tx();
}

void serial_begin_tx_raw(uint8_t length, uint8_t *buffer) {
#ifdef SIMPLEX_UART
    TXIE = 0;
    RCIE = 0;
    CREN = 0;
#endif

    tx_length = length;
    tx_pointer_start = buffer;
    tx_pointer = buffer;

#ifdef SOFTWARE_ECHO_CONTROL
    BUS_DIRECTION = BUS_DIRECTION_TRANSMIT;
#endif
    serial_state = state_tx_data;
    serial_state_since = 0;
#ifdef SIMPLEX_UART
    TXIE = 1;
    TXEN = 1;
#endif
    serial_handle_tx();
}

void func_command_set(void) {
    uint16_t val = serial_rx_buffer[1] + (serial_rx_buffer[2]<<8);
    MACRO_SET_CONF_VAR(serial_rx_buffer[0], val);
}

void func_command_ping(void) {
    serial_begin_tx(ADDRESS_Z, command_reply, sizeof(tx_rombuffer_pong)-1, tx_rombuffer_pong);
}

void serial_tick(void) {
    if (pending_command == 0)
        return;

    int command = pending_command;
    pending_command = 0;
    switch (command) {
    case command_ping: func_command_ping(); break;
    }
}

#ifdef __XC32
static bool _isr_led = true;
void __ISR(_UART2_VECTOR, ipl2) serial_isr(void) {
    led8_set(_isr_led);
    _isr_led = !_isr_led;
    if (IFS1bits.U2RXIF) {
        while (U2STAbits.URXDA)
        {
#ifdef SERIAL_USE_BUS
            serial_handle_rx_bus();
#else
            serial_handle_rx_raw();
#endif
        }
        mU2RXClearIntFlag();
    }
    if (IFS1bits.U2TXIF) {
        while (!U2STAbits.UTXBF) {
            if (!serial_handle_tx()) {
                break;
            }
        }
        mU2TXClearIntFlag();
    }
}

#endif
