// rand.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*init*/
    /*
    int rollNumber = 10;
    for (int crRoll = 1; crRoll <= rollNumber; crRoll++)
    {
        printf("%d\t", 1 + (rand() % 6));
    }
    puts("");
    */

    /*rolling a die 60,000 times and recording frequency*/
    /*
    int rollLimit = 60000000;
    int fr1 = 0, fr2 = 0, fr3 = 0, fr4 = 0, fr5 = 0, fr6 = 0;
    for (int roll = 1; roll <= rollLimit; ++roll)
    {
        int face = 0;
        face = 1 + (rand() % 6);

        switch (face)
        {
        case 1:
            ++fr1;
            // continue; // terminates iteration
            break; // terminates current block of code;
            // break is good-practice here;
        case 2:
            ++fr2;
            // continue; // terminates iteration
            break; // terminates current block of code;
            // break is good-practice here;
        case 3:
            ++fr3;
            // continue; // terminates iteration
            break; // terminates current block of code;
            // break is good-practice here;
        case 4:
            ++fr4;
            // continue; // terminates iteration
            break; // terminates current block of code;
            // break is good-practice here;
        case 5:
            ++fr5;
            // continue; // terminates iteration
            break; // terminates current block of code;
            // break is good-practice here;
        case 6:
            ++fr6;
            // continue; // terminates iteration
            break; // terminates current block of code;
            // break is good-practice here;
        }
    }
    printf("%-10s %-10s\n", "Face", "Freq.");
    printf("%-10d %-10d\n", 1, fr1);
    printf("%-10d %-10d\n", 2, fr2);
    printf("%-10d %-10d\n", 3, fr3);
    printf("%-10d %-10d\n", 4, fr4);
    printf("%-10d %-10d\n", 5, fr5);
    printf("%-10d %-10d\n", 6, fr6);
    */
    
    /*srand randomizing*/
    printf("%s", "Enter seed: ");
    int seed=0; scanf("%d", &seed);
    srand(seed);
    for(int i=1; i<=10; ++i) {
        printf("%d ", 1+(rand()%6));
    }
    puts("");
    return 0;
}