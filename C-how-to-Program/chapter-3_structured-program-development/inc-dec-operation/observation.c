// obserevation.c
// observing pre and post inc

#include <stdio.h>
int main(void)
{

    // -------- pre ---------
    int c = 5;
    printf("%d\n", c);   // c = 5
    printf("%d\n", c++); // post inc, c = 5
    printf("%d\n", c);   // c = 6;

    // -------- pre ---------
    c = 5;
    printf("%d\n", c);   // c = 5;
    printf("%d\n", ++c); // c = 6;
    printf("%d\n", c);   // c = 6

    // -------- syntax-error ! ---------
    // int grade1 = 3, grade2 = 4;
    // int finalGrade = grade1 + grade2;
    // printf("%d\n", ++finalGrade);
    int x=9; 
    int exp = x + 1;
    printf("%d\n", ++exp);
    // printf("%d\n", ++(x+1));
}