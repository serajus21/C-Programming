// write_digits.c
// From a number to a written numeral, by repeated division.
#include <stdio.h>

static void write_digits(unsigned long n, unsigned base) {
    const char symbols[] = "0123456789ABCDEF";
    char reversed[64];                  // enough for 64 binary digits
    int count = 0;
    printf("%lu in base %u:\n", n, base);
    do {
        unsigned long q = n / base;
        unsigned long r = n % base;
        printf("  %lu / %u = %lu, remainder %lu: digit %c\n",
               n, base, q, r, symbols[r]);
        reversed[count++] = symbols[r];
        n = q;
    } while (n != 0);
    printf("  read upward: ");
    while (count > 0)
        putchar(reversed[--count]);
    putchar('\n');
}

int main(void) {
    write_digits(57, 2);
    write_digits(57, 8);
    write_digits(300, 16);
    write_digits(0, 2);
}
