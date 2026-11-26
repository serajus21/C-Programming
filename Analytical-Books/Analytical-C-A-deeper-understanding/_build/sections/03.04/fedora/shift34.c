#include <stdio.h>
#include <stdint.h>
int main(void) {
    volatile uint32_t ten = 10;
    uint64_t wrong = 0; uint32_t first = 0; int seen = 0;
    uint32_t x = 0;
    do {
        if ((uint32_t)(((uint64_t)x * 1717986919u) >> 34) != x / ten) {
            if (!seen) { first = x; seen = 1; }
            ++wrong;
        }
    } while (++x != 0);
    printf("shift 34: %llu mismatches, first at %u\n", (unsigned long long)wrong, (unsigned)first);
    return 0;
}
