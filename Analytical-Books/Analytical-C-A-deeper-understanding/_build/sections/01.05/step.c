// step.c: a tiny program to single-step on the simulated AVR
#include <stdint.h>

volatile uint8_t result;

int main(void) {
    uint8_t a = 6;
    uint8_t b = 7;
    result = a + b;
    for (;;) {}
}
