// same.c
// One quantity, four spellings, and one surprise.
#include <stdio.h>

int main(void) {
    printf("%d %d %d %d\n", 57, 071, 0x39, 0b111001);
    printf("%d %d\n", 0b1010, 0x2F);
    printf("%d\n", 010);
}
