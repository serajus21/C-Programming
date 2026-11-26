// sum.c
// What the program means, and what the machine is made to do.
#include <stdio.h>

int main(void) {
    int total = 0;
    for (int i = 1; i <= 100; ++i) {
        total += i;
    }
    printf("total = %d\n", total);
}
