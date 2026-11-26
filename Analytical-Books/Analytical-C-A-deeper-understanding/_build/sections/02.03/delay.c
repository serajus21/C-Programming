// delay.c
// A busy-wait delay, as beginners often write one.
#include <stdint.h>

void delay_plain(void) {
    for (uint32_t i = 0; i < 200000; ++i) { }     // count, doing nothing
}

void delay_volatile(void) {
    for (volatile uint32_t i = 0; i < 200000; ++i) { }
}
