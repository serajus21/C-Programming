// fig05_01.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* square accepts int
int square(int number);

int main(void)
{
    for (int count = 1; count <= 10; count++)
    {
        printf("%d ", square(count));
    }
    puts("");
    return 0;
}

int square(int number)
{
    return number * number;
}
*/

/*sqrt accepts double*/
double sqRoot(int x) {
    return sqrt(x);
}

int main(void) {
    int x=8;
    double sqrtRes = sqRoot(x);
    printf("%.2f\n", sqrtRes);
}

