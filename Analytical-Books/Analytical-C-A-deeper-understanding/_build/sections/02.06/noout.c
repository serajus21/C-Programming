// noout.c
// printf on a bare ATmega328P, with nothing connected to stdout.
#include <stdio.h>
#include <avr/io.h>

int main(void) {
    int n = printf("hello from the ATmega328P\n");
    DDRB = (1 << DDB5);                 // pin 13 (the Uno's LED) as an output
    if (n < 0) {
        PORTB = (1 << PORTB5);          // LED on: printf reported failure
    }
    for (;;) { }                        // nowhere to return to
}
