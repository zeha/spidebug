#include "common.h"
#include <stdint.h>
#include <stdbool.h>

#include "unit.h"

uint8_t unit_id;

void unit_init(void) {
    // RB6, RB7
    //TRISB6 = TRIS_INPUT;
    //TRISB7 = TRIS_INPUT;
    //unit_id = PORTBbits.RB7;
    //unit_id = (unit_id << 1) | PORTBbits.RB6;
    unit_id = 1;
}
