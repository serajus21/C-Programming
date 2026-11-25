/* Division of nonnegative whole numbers by repeated subtraction. */
#include <stdio.h>

int main(void)
{
    long long dividend;
    long long divisor;
    long long remainder;
    long long quotient = 0;

    printf("Enter a dividend and a divisor (nonnegative whole numbers): ");
    if (scanf("%lld %lld", &dividend, &divisor) != 2) {
        fprintf(stderr, "Please enter two whole numbers.\n");
        return 1;
    }
    if (divisor == 0) {
        fprintf(stderr, "Division by zero is undefined.\n");
        return 1;
    }
    if (dividend < 0 || divisor < 0) {
        fprintf(stderr, "This example accepts nonnegative whole numbers only.\n");
        return 1;
    }

    remainder = dividend;
    printf("Start: remainder = %lld, quotient = %lld\n", remainder, quotient);

    while (remainder >= divisor) {
        remainder -= divisor;
        quotient++;
        printf("Step %lld: subtract %lld; remainder = %lld\n",
               quotient, divisor, remainder);
    }

    printf("Result: %lld divided by %lld = %lld, remainder %lld\n",
           dividend, divisor, quotient, remainder);
    return 0;
}
