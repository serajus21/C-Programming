// divzero.c
// Dividing by zero.
#include <stdio.h>

int main(void) {
    volatile int a = 7, b = 0;      // volatile: no division while compiling
    printf("about to divide\n");
    int q = a / b;
    printf("7 / 0 = %d\n", q);
}
