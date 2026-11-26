// nand.c
// A function with no side effects, like the gates of §01.02.
#include <stdio.h>

static int gate_nand(int a, int b) {
    return !(a && b);               // reads only its arguments, changes nothing
}

int main(void) {
    int table = 0;
    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            table = table * 2 + gate_nand(a, b);    // build 1110 bit by bit
        }
    }
    gate_nand(1, 1);                // result thrown away
    printf("truth table as a number: %d\n", table);
}
