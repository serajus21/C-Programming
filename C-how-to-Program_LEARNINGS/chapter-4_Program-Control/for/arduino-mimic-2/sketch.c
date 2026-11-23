// sketch.c
// this is user's space
// user codes here according to convention set in core.c
// this file can only define and impletement arithmetic();
// NOTHING other than 'arithmetic();

#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "sketch.h"

void arithmetic()
{
    puts("From sketch.c\'s arithmetic() :");
    printf("SUM: %d\n", sum(102,2));
    printf("SUB: %d\n", sub(10,2));
}