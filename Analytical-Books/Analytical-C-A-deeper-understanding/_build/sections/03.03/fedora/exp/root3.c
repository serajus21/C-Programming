#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    printf("%f\n", sqrt(atof(argv[1])));
    return 0;
}
