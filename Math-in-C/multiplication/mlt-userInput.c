// mlt-userInput.c
#include <stdio.h>
int main(void)
{
    int factor1 = 0, factor2 = 0;
    printf("Enter two factors: ");
    scanf("%d %d", &factor1, &factor2);

    int result = 0;

    for (int additionTime = 1; additionTime <= factor1; additionTime++)
    {
        result += factor2;
    }

    printf("%d X %d = %d\n", factor1, factor2, result);
    
}