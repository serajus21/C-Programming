// sum_check.c
#include <stdio.h>

int main(void) {
    double a = 0.1 + 0.2;
    printf("%.2f\n", a);
    printf("%.17f\n", a);
    printf("%d\n", a == 0.3);
}
