// core.c
// this is base of sketch.c

// #include <stdio.h> | UNNECESSARY
// #include <stdlib.h> | UNNECESSARY
#include "core.h"

int main(void)
{
    arithmetic(); // this function is defined in sketch
                  // main has no idea what's sketch.c is putting inside this function
                  // as long as function definition follows C's rule, it'll execute

    return 0;
}