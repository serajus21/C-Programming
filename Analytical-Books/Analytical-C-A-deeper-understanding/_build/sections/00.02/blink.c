// blink.c  (compiled for the ATmega328P; uploading comes in Chapter 36)
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << DDB5);       // pin PB5 (Arduino pin 13): output
    for (;;) {
        PORTB ^= (1 << PORTB5);  // flip the pin: LED on, LED off
        _delay_ms(500);
    }
}
