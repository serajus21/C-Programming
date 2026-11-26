// bcost.c
// What B's model of memory would cost on a byte-addressed machine.
// Compile only (-c) and read the instructions; nothing here is run.
#include <stdint.h>

// 1. Fetching character n of a string.
// The B way: two 8-bit characters packed into each 16-bit word.
unsigned b_char(const uint16_t *s, unsigned n) {
    uint16_t word = s[n / 2];
    return (n % 2 == 0) ? (word >> 8) : (word & 0xFF);
}

// The C way: one character per byte, and every byte has an address.
unsigned c_char(const unsigned char *s, unsigned n) {
    return s[n];
}

// 2. Following a pointer to a 16-bit word.
// The B way: a pointer is a word number; the hardware wants a byte address.
int16_t b_deref(uint16_t word_number) {
    return *(const int16_t *)(uintptr_t)(word_number * 2u);
}

// The C way: the pointer already holds the byte address.
int16_t c_deref(const int16_t *p) {
    return *p;
}
