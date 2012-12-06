#include <xc.h>
#include <plib.h>
#include <stdint.h>
#include <stdbool.h>
#include <p32xxxx.h>

/******************************************************************************/
#define VERSION_MAJOR "00"
#define VERSION_MINOR "01"
/******************************************************************************/

// activate for test / sender circuit!
// #define BUFFER_SENDER

// #define __FILE__
// #pragma message("File: " __FILE__)
#ifdef BUFFER_SENDER
// Transmitter - test version
   #if __FILE__=="main.c"
       #pragma message("Test / Sender Version, Ver.: " VERSION_MAJOR "." VERSION_MINOR)
   #endif
   #undef BUFFER_RECEIVER
#else
// Receiver - production version
//   #warning ("Production Version, Ver.: " VERSION_MAJOR "." VERSION_MINOR)
   // #ifdef main.c
      #pragma message("Production Version, Ver.: " VERSION_MAJOR "." VERSION_MINOR)
      //#undef main.c
   //#endif
   #define BUFFER_RECEIVER
#endif



#undef HAVE_RTCC

// 80MHz
#define SYS_FREQ 80000000L



#define BLOCKDATA_SIZE 10
struct data_stamped {
    uint32_t timestamp;      // 4
    BYTE logdata[47];        // 51
} __attribute__((__packed__)) date_stamped;
typedef struct data_stamped data_stamped;

struct blockdata {
    uint16_t blockid;        // 2
    data_stamped entries[BLOCKDATA_SIZE]; // 2+510=512
} __attribute__((__packed__)); // == 512!!!
typedef struct blockdata blockdata;

/* main.c */
extern volatile unsigned long write_blockid;
extern volatile BOOL write_superblock_pending;
extern volatile uint16_t status_flags;
extern uint32_t config_power_on_delay;

#define STATUS_FLAG_SET_TIME           0x02
#define STATUS_FLAG_ERR_TOO_SLOW       0x10
#define STATUS_FLAG_ERR_REINIT_ESCC    0x20
#define STATUS_FLAG_ERR_INIT_STORAGE   0x40
#define STATUS_FLAG_ERR_INIT_ESCC      0x80
void delay_ms(int time_ms);
void delay_us(int time_us);
#define delay_50nS() {Nop();Nop();Nop();Nop();}

BOOL read_j1(void);
BOOL read_j2(void);
void save_config(void);

/* led.c */
void led1_set(BOOL onoff);
void led2_set(BOOL onoff);
void led3_set(BOOL onoff);
void led4_set(BOOL onoff);
void led5_set(BOOL onoff);
void led6_set(BOOL onoff);
void led7_set(BOOL onoff);
void led8_set(BOOL onoff);
void leds_init(void);

// lcd-color.c
void lcd_demo(void);


/* end */
