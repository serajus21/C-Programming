#include <stdio.h>
#include "headers.h"

int main(void)
{
    int selection;
    long long left, right, integer_result = 0;
    double division_result = 0.0;
    int status;

    puts("Choose an arithmetic operation:");
    puts("1. Sum\n2. Subtraction\n3. Multiplication\n4. Division\n5. Remainder");
    printf("Selection (1-5): ");
    fflush(stdout);
    if (scanf("%d", &selection) != 1 || selection < 1 || selection > 5) {
        fputs("Invalid operation selection.\n", stderr);
        return 1;
    }

    printf("Enter two integers: ");
    fflush(stdout);
    if (scanf("%lld %lld", &left, &right) != 2) {
        fputs("Invalid integers.\n", stderr);
        return 1;
    }

    status = calculate((Operation)selection, left, right,
                       &integer_result, &division_result);
    if (status == 1) {
        fputs("Cannot divide by zero.\n", stderr);
        return 1;
    }
    if (status != 0) {
        fputs("Integer result is out of range.\n", stderr);
        return 1;
    }

    if (selection == OP_DIVIDE)
        printf("Result: %.10g\n", division_result);
    else
        printf("Result: %lld\n", integer_result);
    return 0;
}
