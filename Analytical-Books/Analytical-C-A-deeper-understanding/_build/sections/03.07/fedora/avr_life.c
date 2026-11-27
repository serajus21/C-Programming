// avr_life.c  (ATmega328P)
// One variable with an initializer, one without, and a main that returns.
#include <avr/io.h>

unsigned char ready = 0x5A;     // .data: its initial value is copied from flash at start-up
unsigned char count;            // .bss: cleared to zero at start-up

int main(void) {
    DDRB = (unsigned char)(ready + count);   // use both, so that neither is removed
    return 7;                                // and then: to whom?
}
