// avr_led.c  (ATmega328P)
// What PORTB and PB5 really are.
#include <avr/io.h>

int main(void) {
    DDRB |= (1 << DDB5);     // pin 13 (PB5) as an output
    PORTB |= (1 << PB5);     // drive it high: the LED lights
    for (;;) { }
}
