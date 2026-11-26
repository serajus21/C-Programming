// flag.c
// Waiting for a flag that something outside this code will set.
#include <stdint.h>

uint8_t ready;                      // set elsewhere, e.g. by an interrupt
volatile uint8_t ready_v;           // the same, declared volatile

void wait_plain(void) {
    while (!ready) { }              // wait until ready becomes nonzero
}

void wait_volatile(void) {
    while (!ready_v) { }
}
