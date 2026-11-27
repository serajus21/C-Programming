// avr_bases.c
// The same repeated division, on an 8-bit chip with no divide instruction.
#include <stdio.h>
#include <avr/io.h>

static void print_in_base(unsigned n, unsigned base) {
    const char symbols[] = "0123456789ABCDEF";
    char reversed[16];                  // an unsigned is 16 bits here
    int count = 0;
    do {
        reversed[count++] = symbols[n % base];
        n = n / base;
    } while (n != 0);
    while (count > 0)
        putchar(reversed[--count]);
    putchar('\n');
}

int main(void) {
    print_in_base(57, 2);
    print_in_base(57, 16);
    print_in_base(RAMEND, 16);
    printf("%u %o %x %X\n", 57, 57, 57, 0x2F);
    printf("PORTB: data address 0x%02X\n", _SFR_MEM_ADDR(PORTB));
}
