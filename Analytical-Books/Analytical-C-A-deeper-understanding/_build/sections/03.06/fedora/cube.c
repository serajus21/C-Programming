// cube.c
// A function from the math library, with an argument known only when the program runs.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    double x = (argc > 1) ? strtod(argv[1], NULL) : 27.0;
    printf("%g\n", cbrt(x));
    return 0;
}
