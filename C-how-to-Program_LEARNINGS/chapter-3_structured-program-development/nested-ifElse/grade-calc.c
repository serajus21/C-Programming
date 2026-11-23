// grade-calc.c
// using nested if...else...
/* pseudocode
    if students grade is less then 0 or greater than 100
        print 'Invalid'
    else
    --------------
        if student's grade is greater than or  equal to 90
            print 'A'
        else
        --------------
            if student's grade is greater than or  equal to 80
                print 'B'
            else
            --------------
                if student's grade is greater than or  equal to 70
                    print 'C'
                else
                --------------
                    if student's grade is greater than or  equal to 60
                        print 'D'
                    else
                    --------------
                        print 'failed'...
*/

#include <stdio.h>

int main(void)
{
    int grade = 0;
    printf("Enter grade: ");
    scanf("%d", &grade);

    if (grade < 0 || grade > 100)
    {
        puts("INVALID INPUT\n");
    }
    else
    {
        if (grade >= 90)
        {
            puts("A");
        }
        else
        {
            if (grade >= 80)
            {
                puts("B");
            }
            else
            {
                if (grade >= 70)
                {
                    puts("C");
                }
                else
                {
                    if (grade >= 60)
                    {
                        puts("D");
                    }
                    else
                    {
                        puts("Failed");
                    }
                }
            }
        }
    }
}


