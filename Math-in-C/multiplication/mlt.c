// mlt.c
#include <stdio.h>

/* number of times value needs to be increased | with variable
int main(void)
{
    int op1 = 3, op2 = 4; // factor variables | 3 * 4 => 3 Times 4; meaning value is increasing by 4; three times
    int op1Array[op1] = {op1, op1, op1}; // number of times value needs to be increased
    int op1ArrLength = sizeof(op1Array) / sizeof(op1Array[0]);

    int result = 0; // result store

    for (int op1ArIndex = 0; op1ArIndex < op1ArrLength; op1ArIndex++)
    {

        // as multiplication is conceptually continue addition;
        // I keep adding factor-4 until it reaches it's limit of another factor-3;
        result += op2;
    }

    printf("%d X %d = %d\n", op1, op2, result);
    return 0;
}
*/


//number of times value needs to be increased | with static value
int main(void)
{
    int op1 = 3, op2 = 4;              // factor variables | 3 * 4 => 3 Times 4; meaning value is increasing by 4; three times
    int op1Array[3] = {op1, op1, op1}; // number of times value needs to be increased
    int op1ArrLength = sizeof(op1Array) / sizeof(op1Array[0]);

    int result = 0; // result store

    for (int op1ArIndex = 0; op1ArIndex < op1ArrLength; op1ArIndex++)
    {

        // as multiplication is conceptually continue addition;
        // I keep adding factor-4 until it reaches it's limit of another factor-3;
        result += op2;
    }

    printf("%d X %d = %d\n", op1, op2, result);
    return 0;
}