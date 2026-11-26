// check10.c
// Is (x * 3435973837) >> 35 equal to x / 10 for every 32-bit x?
#include <stdio.h>
#include <stdint.h>

int main(void) {
    volatile uint32_t ten = 10;        // volatile: forces a real division
    uint64_t wrong = 0, wrong_m1 = 0;
    uint32_t x = 0;
    do {
        uint32_t q = x / ten;
        if ((uint32_t)(((uint64_t)x * 3435973837u) >> 35) != q) {
            ++wrong;                   // the compiler's constant
        }
        if ((uint32_t)(((uint64_t)x * 3435973836u) >> 35) != q) {
            ++wrong_m1;                // one less
        }
    } while (++x != 0);                // after 4294967295, x wraps to 0
    printf("mismatches with 3435973837: %llu\n", (unsigned long long)wrong);
    printf("mismatches with 3435973836: %llu\n", (unsigned long long)wrong_m1);
    return 0;
}
