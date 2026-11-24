// warnings.c
#include <stdio.h>

int square(int x, int unused) {
    return x * x;
}

int main(void) {
    int y;
    printf("%d\n", square(3, 0));
}
