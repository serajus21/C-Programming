// count.c
// printf returns a value, which hello.c silently threw away.
#include <stdio.h>

int main(void) {
    int n = printf("hello, world\n");
    printf("printf reported %d characters\n", n);
    printf("the literal occupies %zu bytes\n", sizeof "hello, world\n");
    return 0;
}
