// choices.c
// Ask the implementation some questions the C standard leaves to it.
#include <stdio.h>
#include <limits.h>

int main(void) {
    printf("bits in a byte (CHAR_BIT): %d\n", CHAR_BIT);
    printf("plain char is:             %s\n", CHAR_MIN < 0 ? "signed" : "unsigned");
    printf("bytes in an int:           %u\n", (unsigned)sizeof(int));
    printf("largest int (INT_MAX):     %ld\n", (long)INT_MAX);

    char c = (char)200;             // 200 does not fit in a signed 8-bit char
    printf("(char)200 reads back as:   %d\n", c);

    int n = -7;
    printf("-7 >> 1 gives:             %d\n", n >> 1);
    printf("-7 / 2 and -7 %% 2 give:    %d and %d\n", n / 2, n % 2);
}
