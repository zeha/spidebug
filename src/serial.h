#ifndef SERIAL_H
#define	SERIAL_H

void serial_init(void);
void serial_tick(void);

void serial_handle_rx_bus(void);
void serial_handle_rx_raw(void);
bool serial_handle_tx(void);
void serial_begin_tx_bus(uint8_t address, uint8_t command, uint8_t length, uint8_t *buffer);
void serial_begin_tx_raw(uint8_t length, uint8_t *buffer);

extern uint8_t serial_tx_buffer[SERIAL_BUFFER_SIZE];
extern uint8_t serial_rx_buffer[SERIAL_BUFFER_SIZE];
extern uint8_t *serial_rx_pointer;

#endif
