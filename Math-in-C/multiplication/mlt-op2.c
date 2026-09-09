//mlt-op2.c
#include<stdio.h>

int main(void) {
    int op1 = 3, op2 = 4;
    int op2Array[3] = {op2,op2,op2};
    int op2ArrLength = sizeof(op2Array) / sizeof(op2Array[0]);

    int result = 0;

    for(int op2ArIndex=0; op2ArIndex<op2ArrLength; op2ArIndex++) {
        result += op2Array[op2ArIndex];
    }

    printf("%d X %d = %d\n", op1,op2,result);
    return 0;
}