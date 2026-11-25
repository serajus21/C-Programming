// decoder.c
// A 3-to-8 decoder built from AND and NOT: exactly one output is 1.
#include <stdio.h>

int main(void) {
    printf("A2 A1 A0 | outputs 7..0\n");
    for (int addr = 0; addr < 8; ++addr) {
        int a2 = (addr >> 2) & 1;
        int a1 = (addr >> 1) & 1;
        int a0 = addr & 1;
        printf(" %d  %d  %d | ", a2, a1, a0);
        for (int line = 7; line >= 0; --line) {
            int want2 = (line >> 2) & 1;    // the address this line wants
            int want1 = (line >> 1) & 1;
            int want0 = line & 1;
            int t2 = want2 ? a2 : !a2;      // the input itself, or its NOT
            int t1 = want1 ? a1 : !a1;
            int t0 = want0 ? a0 : !a0;
            printf("%d", t2 && t1 && t0);   // a three-input AND
        }
        printf("\n");
    }
}
