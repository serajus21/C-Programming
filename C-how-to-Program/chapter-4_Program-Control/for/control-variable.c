// control-variable.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* experimenting increment in body | infinite loop*/
    /*
    int limit = 10;
    for (int controlVar = 0; controlVar <= limit;)
    {
        printf("%d\t", controlVar);

        // if(controlVar == 5) {continue;} // loop never ends, cause controlVar never increments after 5;
                                           // continue never allows controlVar to reach controlVar++; it terminates iteration
                                           // so, controlVar always remains 5 | an infinite loop

        // for clearer observation
        if (controlVar == 5)
        {
            for (int i = 0; i < 5; i++)
            {
                printf("%d(%d)\t", controlVar, i + 1);
                continue;
            }
        }

        controlVar++;
    }
    puts("");
    return 0;
    */

    /*experimenting increment in body | INTENDED */
    for (int i = 0; i < 10;)
    {
        if (/*operation failed*/ NULL)
        {
            continue;
        }

        printf("%d\t", i);
        i++;
    }
    puts("");
}
