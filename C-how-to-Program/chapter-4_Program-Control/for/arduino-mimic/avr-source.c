// avr-source.c
// pretending as .ino file
#include <stdio.h>
#include <stdlib.h>
#include "avr-header.h"

void arithmetic()
{
    puts("EXPERIMENTING ARDUINO");
    printf("Sum: %d\n", sum(2,3));
    printf("Sub: %d\n", sub(3,2));
}