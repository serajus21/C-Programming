// core.c

#include "core.h"

int main(void)
{
    setup();
    for (;;)
    {
        loop();
    }

    return 0;
}