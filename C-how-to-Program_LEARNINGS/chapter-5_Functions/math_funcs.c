// math_funcs.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int leastNumber = 0, greatestNumber = 0;
    printf("Enter least and greatest number: ");
    scanf("%d %d", &leastNumber, &greatestNumber);
    
    printf("%-10s%-10s\n", "Number", "Root");
    printf("%-10s%-10s\n", "--------", "------");

    // for (int number = 900; number >= 800; number--)
    // {
    //     double sqrt_result_of_number = sqrt((double)number);
    //     printf("%-10.2f%-10.2f\n", (double)number, sqrt_result_of_number);
    // }

    while (leastNumber <= greatestNumber)
    {
        double sqrt_result_of_number = sqrt((double)greatestNumber);
        printf("%-10.2f%-10.2f\n", (double)greatestNumber, sqrt_result_of_number);
        greatestNumber--;
    }

    puts("");
    return 0;
}