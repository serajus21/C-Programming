// array-add.c
#define divider "________________________________________________\n"
#define processing "processing...................................\n"

#include <stdio.h>
int main(void)
{
    int ar1[2][3] = {};
    int ar2[2][3] = {};
    int sum[2][3] = {};

    printf("---------Array-1---------\n");
    for (int ri = 0; ri < 2; ri++)
    {
        for (int ci = 0; ci < 3; ci++)
        {
            printf("arr1[%d][%d] = ", ri, ci);
            scanf("%d", &ar1[ri][ci]);
        }
    }
    printf("---------Array-2---------\n");
    for (int ri = 0; ri < 2; ri++)
    {
        for (int ci = 0; ci < 3; ci++)
        {
            printf("arr2[%d][%d] = ", ri, ci);
            scanf("%d", &ar2[ri][ci]);
        }
    }

    printf(divider);
    printf(processing);

    printf("---------Array-1 OUTPUT---------\n");
    for (int ri = 0; ri < 2; ri++)
    {
        for (int ci = 0; ci < 3; ci++)
        {
            printf("%d\t", ar1[ri][ci]);
        }
        puts("");
    }
    printf("---------Array-2 OUTPUT---------\n");
    for (int ri = 0; ri < 2; ri++)
    {
        for (int ci = 0; ci < 3; ci++)
        {
            printf("%d\t", ar2[ri][ci]);
        }
        puts("");
    }
    printf("---------(Array-1) + (Array-2)---------\n");
    for (int ri = 0; ri < 2; ri++)
    {
        for (int ci = 0; ci < 3; ci++)
        {
            sum[ri][ci] = ar1[ri][ci] + ar2[ri][ci];
            printf("%d\t", sum[ri][ci]);
        }
        puts("");
    }

    return 0;
}