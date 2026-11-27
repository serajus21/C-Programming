// read_digits.c
// From a written numeral to a number, one digit at a time.
#include <stdio.h>

static int digit_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;                          // not a digit in any base up to 16
}

static void read_digits(const char *text, unsigned base) {
    unsigned long value = 0;
    printf("\"%s\" in base %u:\n", text, base);
    for (const char *p = text; *p != '\0'; ++p) {
        int d = digit_value(*p);
        if (d < 0 || (unsigned)d >= base) {
            printf("  '%c' is not a digit in base %u\n", *p, base);
            return;
        }
        printf("  %lu x %u + %d = %lu\n", value, base, d, value * base + d);
        value = value * base + d;
    }
    printf("  value: %lu\n", value);
}

int main(void) {
    read_digits("307", 10);
    read_digits("111001", 2);
    read_digits("71", 8);
    read_digits("2F", 16);
    read_digits("19", 8);
}
