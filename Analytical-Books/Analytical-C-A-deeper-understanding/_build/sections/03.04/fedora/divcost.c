// divcost.c
// How long does a division take, against the compiler's multiplication?
#include <stdio.h>
#include <stdint.h>
#include <time.h>

static double now(void) {
    struct timespec t;
    timespec_get(&t, TIME_UTC);        // standard C since C11
    return (double)t.tv_sec + (double)t.tv_nsec / 1e9;
}

int main(void) {
    volatile uint32_t ten_v = 10;
    uint32_t ten = ten_v;              // a 10 known only when the program runs
    const uint32_t n = 500000000;
    uint32_t a = 1, b = 1;

    double t0 = now();
    for (uint32_t i = 0; i < n; ++i) {
        a = (a + i) / ten;             // must use a division instruction
    }
    double t1 = now();
    for (uint32_t i = 0; i < n; ++i) {
        b = (b + i) / 10;              // the compiler multiplies instead
    }
    double t2 = now();
    printf("divide by a variable 10: %.2f ns per step\n", (t1 - t0) / n * 1e9);
    printf("divide by the constant 10: %.2f ns per step\n", (t2 - t1) / n * 1e9);
    printf("results: %u %u\n", (unsigned)a, (unsigned)b);
    return 0;
}
