// counter.c
#include <stdint.h>

uint16_t count;

void tick(void) {
    count = count + 1;
}
