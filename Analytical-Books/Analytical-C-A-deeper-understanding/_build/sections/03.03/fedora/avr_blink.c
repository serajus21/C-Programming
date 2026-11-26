// avr_blink.c  (ATmega328P at 16 MHz)
// A header that brings a function body with it.
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << DDB5);
    for (;;) {
        PORTB ^= (1 << PB5);     // toggle the LED
        _delay_ms(500);
    }
}
