// brace.c
// A missing closing brace, reported far from where it is missing.
#include <stdio.h>

static int twice(int x) {
    if (x > 0) {
        return 2 * x;
                        // the '}' of the if is missing
    return 0;
}

int main(void) {
    printf("%d\n", twice(21));
    return 0;
}
