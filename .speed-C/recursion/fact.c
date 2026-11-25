// fact.c
//  understanding recursion

#include <stdio.h>

int fact(int n); // prototype

int main(void)
{ // main init
    int n = 5;
    int factorial = fact(n);
    printf("Factorial of %d: %d\n", n,factorial);
} // main terminate

// function definition
int fact(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * fact(n - 1);
    }
}