// counter.c
#include <stdint.h>

uint8_t count;

void tick(void) {
    count = count + 1;
}
