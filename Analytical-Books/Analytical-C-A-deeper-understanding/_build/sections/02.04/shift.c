// shift.c
// Shifting a 32-bit value by 32 places.
#include <stdio.h>
#include <stdint.h>

int main(void) {
    volatile int n = 32;            // volatile: the compiler cannot know n
    uint32_t x = 1;
    printf("1 << %d = %lu\n", n, (unsigned long)(x << n));
}
