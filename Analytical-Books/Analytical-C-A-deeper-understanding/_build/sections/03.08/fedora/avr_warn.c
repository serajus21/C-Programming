// avr_warn.c  (ATmega328P)
// A pin that does not exist, and a delay without F_CPU.
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB = 1 << 8;                      // PB8 does not exist (bits 0-7)
    for (;;) {
        PORTB ^= 1 << 5;
        _delay_ms(500);
    }
}
