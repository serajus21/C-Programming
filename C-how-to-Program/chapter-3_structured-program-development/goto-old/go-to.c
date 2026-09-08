// go-to.c
// understanding goto statement to understand why selection and iteration structure is needed.

#include <stdio.h>

int main(void)
{
    int init = 1;
    int limit = 5;

printLimit:
    printf("%d\t", init);
    if(init == 5) {
        printf("\n");
    }
    init++;

    if (init <= limit)
        goto printLimit;

    return 0;
}
