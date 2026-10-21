// avr-main.c
// pretending as arduino-core

#include <stdio.h>
#include <stdlib.h>
#include "avr-header.h"
// void arithmetic(); // should i create seperate header files for core and sketch (avr-source)? YES-WE-CAN

int main(void)
{
    // puts("Seperate HEADER");
    arithmetic();

    return 0;
}