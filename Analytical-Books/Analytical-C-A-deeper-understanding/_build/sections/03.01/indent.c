// indent.c
// The layout says one thing, the tokens another.
#include <stdio.h>

int check(int err) {
    if (err != 0)
        printf("first check failed\n");
        return 1;
    printf("all checks passed\n");
    return 0;
}

int main(void) {
    return check(0);
}
