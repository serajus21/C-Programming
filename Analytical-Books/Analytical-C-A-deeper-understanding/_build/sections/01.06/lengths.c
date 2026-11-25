// lengths.c: three functions whose x86-64 instructions differ in length
#include <stdint.h>

uint8_t add8(uint8_t a, uint8_t b) {
    return a + b;
}

long add_big(long x) {
    return x + 0x123456789;     // a constant too big for 32 bits
}

long times10(long x) {
    return x * 10;
}
