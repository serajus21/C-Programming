// escape.c
// Escape sequences are converted (phase 5) before literals are joined (phase 6).
#include <stdio.h>
#define NAME "world"

int main(void) {
    printf("hello, " NAME "\n");             // three literals become one
    printf("%s\n", "\x41" "BC");              // 'A', then "BC"
    printf("%zu\n", sizeof "\x41" "BC");      // the size of the joined literal
    return 0;
}
