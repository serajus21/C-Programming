// printf_bases.c
// Asking printf to write one value in four bases.
#include <stdio.h>

int main(void) {
    unsigned x = 57;
    printf("decimal  %u\n", x);
    printf("octal    %o    %#o\n", x, x);
    printf("hex      %x    %X    %#x    %#X\n", x, x, x, x);
    printf("binary   %b    %#b\n", x, x);
    printf("padded   [%08b]  [%04X]  [%8x]  [%#06x]\n", x, x, x, x);
    unsigned big = 3735928559;
    printf("big      %u = %#x = %#o\n", big, big, big);
}
