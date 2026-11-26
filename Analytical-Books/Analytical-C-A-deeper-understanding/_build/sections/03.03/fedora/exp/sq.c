#include <stdio.h>
#define SQUARE(x) x * x
int main(void) {
    printf("%d\n", 100 / SQUARE(5));
    return 0;
}
