// hexdump_me.c
// Write a few known bytes to a file, then look at them with xxd.
#include <stdio.h>

int main(void) {
    FILE *f = fopen("bytes.bin", "wb");
    if (f == NULL) return 1;
    unsigned char bytes[] = {0x7F, 'E', 'L', 'F', 57, 0x39, 071, 0b111001, 255, 0};
    fwrite(bytes, 1, sizeof bytes, f);
    fclose(f);
}
