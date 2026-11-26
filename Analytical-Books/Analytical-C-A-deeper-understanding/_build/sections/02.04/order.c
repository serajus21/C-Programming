// order.c
// Which operand is evaluated first? The standard does not say.
#include <stdio.h>

static int trace(const char *name, int value) {
    printf("%s ", name);            // a visible side effect
    return value;
}

int main(void) {
    int sum = trace("a", 1) + trace("b", 2);
    printf("-> sum %d\n", sum);
    printf("-> %d %d\n", trace("c", 3), trace("d", 4));
}
