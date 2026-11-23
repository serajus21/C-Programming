// plain-program.c
// remembering ternary operator, known as also conditional operator

#include <stdio.h>
int gradeCalc(int grade); // prototype

int main(void) // main
{
    int userGrade = 0;
    printf("Enter Your Grade: ");
    scanf("%d", &userGrade);

    gradeCalc(userGrade); // function call

    return 0;
}

int gradeCalc(int grade) // function definition
{
    (grade >= 60) ? puts("Passed") : puts("Failed");
}
