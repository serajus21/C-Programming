// where.c
// Print where main, a global, a local and puts are in memory.
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int global = 1;

int main(void) {
    int local = 2;
    printf("main   0x%" PRIxPTR "\n", (uintptr_t)main);
    printf("global %p\n", (void *)&global);
    printf("local  %p\n", (void *)&local);
    printf("puts   0x%" PRIxPTR "\n", (uintptr_t)puts);
    return local - 2;
}
