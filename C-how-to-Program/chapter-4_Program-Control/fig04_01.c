//fig04_01.c
// counter-controlled interation

#include<stdio.h>
int main(void) {
    int counter = 1;

    while (counter<=5) 
    {
        // ++counter; // 2 3 4 5
        printf("%d ", counter);
        ++counter; // 1 2 3 4 5
    }

    puts("");
    printf("Termination Counter Value: %d\n", counter);
    
}