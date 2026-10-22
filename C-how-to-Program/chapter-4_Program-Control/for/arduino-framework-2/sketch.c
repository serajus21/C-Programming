// sketch.c

#include "core.h"
#include "funcsLib.h"

void setup(void)
{
    setupMessage("Hello, from sketch.c");
}

void loop(void)
{
    for (int time = 1; time <= 2; time++)
    {
        digitalWrite(13, 1);
        delay(1);
        digitalWrite(13, 0);
        delay(1);
    }

    setupMessage("DONE");
}
