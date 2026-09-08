//inside-printf.c
//using ternary as argument inside printf, where if...else can't be used;

#include <stdio.h>

int main(void) // main
{
    int userGrade = 0;
    printf("Enter Your Grade: ");
    scanf("%d", &userGrade);

    printf("%s\n", ((userGrade >= 60) ? "passed" : "failed"));

    return 0;
}
