// avr_ops.c  (ATmega328P)
// ops.c's division, linked into a program, to see what it costs.
#include <avr/io.h>

unsigned div10(unsigned x) {
    return x / 10;
}

int main(void) {
    unsigned v = PINB;                 // a value the compiler cannot know
    PORTB = (unsigned char)div10(v);
    for (;;) { }
}
