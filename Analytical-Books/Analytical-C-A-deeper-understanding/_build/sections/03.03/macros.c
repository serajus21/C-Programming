// macros.c
// A first look at macros: text replaced by text, before the compiler reads it.
#include <stdio.h>

#define LIMIT 10                 // an object-like macro
#define SQUARE(x) x * x          // a function-like macro, written carelessly
#define SQUARE_OK(x) ((x) * (x)) // the same, written carefully

int main(void) {
    printf("%d\n", LIMIT);
    printf("%d\n", SQUARE(3));
    printf("%d\n", SQUARE(1 + 2));
    printf("%d\n", SQUARE_OK(1 + 2));
    return 0;
}
