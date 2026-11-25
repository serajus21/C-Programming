//div.c
//division with core logics | static

#include <stdio.h>

int main(void) {
    int op_1 = 10;
    int op_2 = 5;
    int reductionCounter = 0;

    puts("|-first-operand-must-be-larger-|");
    printf("%s", "Enter two operands: ");
    scanf("%d %d", &op_1, &op_2);

    while (op_1 > 0)
    {
        op_1 -= op_2;
        reductionCounter++;
    }

    printf("%d\n", reductionCounter);
}