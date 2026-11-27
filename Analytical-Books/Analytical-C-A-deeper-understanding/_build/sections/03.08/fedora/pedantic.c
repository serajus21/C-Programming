// pedantic.c
// Two GNU extensions: accepted in silence until -pedantic is given.
#include <stdio.h>

int main(void) {
    int empty[0];                                      // zero-length array
    int max = ({ int a = 3, b = 4; a > b ? a : b; });  // statement expr.
    printf("%zu %d\n", sizeof empty, max);
    return 0;
}
