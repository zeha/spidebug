/*
 * File:   main.c
 * Author: wh
 *
 * Created on 30. Nov. 2012, 22:02
 */

#include "common.h"
#include <stdbool.h>

// EEPROM Lib
#include <peripheral/nvm.h>
#define NVMOP_PAGE_ERASE        0x4004      // Page erase operation
extern unsigned int _NVMOperation(unsigned int nvmop);
// EEPROM Lib

//Zeiger auf eine 32Bit VIRTUELLE Adresse, bei absoluten Adressen bekommst du einen Fehler
//uint32_t EEPROM_address = 0x9D008000;   // == 0x1d008000 phys    CACHED KSEG0
uint32_t EEPROM_address = 0xBD008000;     // == 0x1d008000 phys UN-CACHED KSEG1

//#define NVM_CONFIG_PAGE_PHYS 0x1D007FFC
// #define NVM_CONFIG_PAGE_VIRT 0xBD007FFC  // 9D

#define ONE_MS (SYS_FREQ/2000)

volatile unsigned long write_blockid = 0;
volatile uint16_t status_flags = 0;
uint32_t config_power_on_delay = 0;

// ------------------------------

unsigned int NVMUnlock (unsigned int nvmop) {
    unsigned int status;
    // Suspend or Disable all Interrupts
    asm volatile ("di %0" : "=r" (status));
    // Enable Flash Write/Erase Operations and Select
    // Flash operation to perform
    NVMCON = nvmop;
    // Write Keys
    NVMKEY = 0xAA996655;
    NVMKEY = 0x556699AA;
    // Start the operation using the Set Register
    NVMCONSET = 0x8000;
    // Wait for operation to complete
    while (NVMCON & 0x8000);
    // Restore Interrupts
    if (status & 0x00000001) {
    asm volatile ("ei");}
   else {
    asm volatile ("di");
   }
    // Disable NVM write enable
    NVMCONCLR = 0x0004000;
    // Return WRERR and LVDERR Error Status Bits
    return (NVMCON & 0x3000);
}

//----------------

// void save_config(void* EEPROM_address, unsigned int data) {
void save_config(void) {

    int res;
    uint32_t buffer[1024];

    if (config_power_on_delay > 20)
        config_power_on_delay = 0;

    buffer[0] = config_power_on_delay;
    buffer[1] = 0xaa55aa55;

    res = NVMErasePage((void*)EEPROM_address);

    // Convert Address to Physical Address
    // NVMADDR = KVA_TO_PA((unsigned int)EEPROM_address);
    // Unlock and Erase Page
    // res = NVMUnlock(NVMOP_PAGE_ERASE);
   // res = _NVMOperation(NVMOP_PAGE_ERASE);

    res = NVMWriteRow((void*)EEPROM_address, (void*)buffer);

    config_power_on_delay = *((uint32_t*)(EEPROM_address));

    while (res != 0);
    
//
//    unsigned long t0 = _CP0_GET_COUNT(); /* Used for NVMOP 6 us Delay */
//
//    NVMCON = 0x4001;            /* set WREN and Word Programing mode */
//    NVMADDR = NVM_CONFIG_PAGE_PHYS;  /* PM Address at which we'll store the */
//                                /* cause register */
//    NVMDATA   = config_power_on_delay;
//
//    INTDisableInterrupts();
//    /* wait at least 6 us for LVD start-up
//    assume we're running at max frequency
//    (80 MHz) so we're always safe */
//    {
//        while (_CP0_GET_COUNT() - t0 < (80/2)*6);
//    }
//
//    NVMKEY    = 0xAA996655;
//    NVMKEY    = 0x556699AA;     /* unlock sequence */
//    NVMCONSET = NVMCON_WR;
//    while(NVMCON & NVMCON_WR);  /* wait on write to finish */
//
//    INTEnableInterrupts();



}


void delay_ms(int time_ms) {
    unsigned int start, wait;
    wait = ONE_MS * time_ms;
    start = ReadCoreTimer();
    while ((ReadCoreTimer()-start) < wait);
}

void delay_us(int time_us) {
    unsigned int start, wait;
    wait = (ONE_MS/1000) * time_us;
    start = ReadCoreTimer();
    while ((ReadCoreTimer()-start) < wait);
}


BOOL read_j1(void) {
    return (mPORTBReadBits(BIT_6) & BIT_6) == 0;
}
BOOL read_j2(void) {
    return (mPORTBReadBits(BIT_7) & BIT_7) == 0;
}

void rtc_init(void) {
#ifdef HAVE_RTCC
    RtccInit();
    while (RtccGetClkStat() != RTCC_CLK_ON); // wait for RTC to come up
#else
    return; // no RTC
#endif
}

void init(void) {
    DDPCONbits.JTAGEN = 0;
    SYSTEMConfigPerformance(SYS_FREQ);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);


    //Wert der Adresse lesen
//    config_power_on_delay = *((uint32_t*)(EEPROM_address));
    // config_power_on_delay = *((int*)(NVM_CONFIG_PAGE_VIRT));
//    if (config_power_on_delay > 20)
//        config_power_on_delay = 0;
//    delay(config_power_on_delay*1000);

    leds_init();
    lcd_init();

//    INTEnableInterrupts();
    delay_ms(100);

    // USB?
}


unsigned long __stack_chk_guard = 0xFAFAFAFA;
void __attribute__ ((noreturn)) __stack_chk_fail(void) {
    bool led = false;
    int i = 0;
    for (i=0; i<60000; i++) {
        led1_set(FALSE);
        led2_set(FALSE);
        led3_set(FALSE);
        led4_set(!led);
        delay_ms(100);
    }
    SoftReset();
}

int main(void) {
    int last_dataid = 0;
    unsigned long startup_time;

    init();

    while (1) {
        led1_set(FALSE);
        led7_set(TRUE);
        led8_set(TRUE);
        delay_ms(100);
        led1_set(TRUE);
        led7_set(FALSE);
        led8_set(FALSE);
        delay_ms(400);
        lcd_demo_loop();

// Main Loop
    }
}
