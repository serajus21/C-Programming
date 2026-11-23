// funcsLib.c

#include <stdio.h>
#include <stdlib.h>
#include "funcsLib.h"

void setup(void)
{
    puts("SETTING UP...");
}

void loop(void)
{
    digitalWrite(13,1);
    delay(1000);
    digitalWrite(13,0);
    delay(1000);
}
