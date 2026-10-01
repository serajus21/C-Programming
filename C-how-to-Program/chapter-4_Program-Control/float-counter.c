// float-counter.c

/**/
#include <stdio.h>
int main(void)
{
    /* floating-point value controls the counter | floating-point is displayed
    double counter = 0.00;
    // while (counter <= 1.00)
    while (counter <= 1.01)
    {
        printf("%.30f\n", counter);
        counter += 0.05;
    }
    puts("");
    */

    /* integer controls the counter | floating-point is displayed */
    int counter = 0;
    while (counter <= 20)
    {
        printf("%.2f\t", counter / 20.0);
        ++counter;
    }
    puts("");
}