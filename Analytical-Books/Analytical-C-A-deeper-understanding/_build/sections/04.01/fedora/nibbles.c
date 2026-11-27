// nibbles.c
// The sixteen patterns of four bits, in four notations.
#include <stdio.h>

int main(void) {
    printf("dec  bin   oct  hex\n");
    for (unsigned n = 0; n < 16; ++n)
        printf("%3u  %04b  %3o  %3X\n", n, n, n, n);
}
