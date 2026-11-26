// ops.c
// Each C operation below maps onto very few machine instructions.
#include <stdint.h>

uint8_t mask(uint8_t a)  { return a & 0x0F; }       // keep the low 4 bits
uint8_t twice(uint8_t a) { return (uint8_t)(a << 1); }
int     add(int a, int b) { return a + b; }
uint8_t fetch(const uint8_t *p) { return *p; }
void    set_bit5(volatile uint8_t *reg) { *reg |= 1u << 5; }
