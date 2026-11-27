// avr_div.c  (ATmega328P)
// One division by a number known only at run time.
#include <avr/io.h>

int main(void) {
    volatile unsigned int n = 1000, d = 7;   // volatile: the compiler must not fold them
    PORTB = (unsigned char)(n / d);
    for (;;) { }
}
