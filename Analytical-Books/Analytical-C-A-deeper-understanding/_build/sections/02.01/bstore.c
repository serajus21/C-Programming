#include <stdint.h>
void b_lchar(uint16_t *s, unsigned n, unsigned c) {
    uint16_t *w = &s[n / 2];
    if (n % 2 == 0) *w = (uint16_t)((*w & 0x00FF) | (c << 8));
    else            *w = (uint16_t)((*w & 0xFF00) | (c & 0xFF));
}
void c_lchar(unsigned char *s, unsigned n, unsigned c) {
    s[n] = (unsigned char)c;
}
