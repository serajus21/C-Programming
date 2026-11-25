// init-2D.c

#include <stdio.h>
int main(void)
{
    /*
    int array_2D_init[10][10] = {
        {1, 2, 3, 59, 8, 98, 87, 5, 87, 98},   // row1
        {4, 5, 6, 5, 8, 89, 26, 74, 87, 58} // row2
    };

    // printf("r0c1: %d\n", array_2D_init[1][1]);
    // printf("r1c2: %d\n", array_2D_init[1][2]);

    for (int ri = 0; ri < 2; ri++)
    {
        for (int ci = 0; ci < 10; ci++)
        {
            printf("%d\t", array_2D_init[ri][ci]);
        }
        puts("");
    }
    */

    int userInput[2][2] = {};
    int rowLength = 2, colLength = 2;

    for (int ri = 0; ri < rowLength; ri++)
    {
        for (int ci = 0; ci < colLength; ci++) {
            printf("Enter for row_%d col_%d: ", ri+1,ci+1);
            scanf("%d", &userInput[ri][ci]);
        }
    }

    for (int ri = 0; ri < rowLength; ri++)
    {
        for (int ci = 0; ci < colLength; ci++) {
            printf("%d\t", userInput[ri][ci]);
        }
        puts("");
    }
    
}