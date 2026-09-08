#include<stdio.h>
int main(void) {
    int passed = 0, failed = 0, counter = 1;
    
    while (counter <= 10)
    {
        counter++;
        printf("%s", "Enter Status | 1. Passed | 2. Failed: ");
        int status = 0;
        scanf("%d", &status);

        if(status == 1) {
            passed++;
        } else {
            failed++;
        }
    }

    printf("Passed: %d | Failed: %d\n", passed, failed);
    if(passed >=8) {
        printf("%s", "Bonus to instructor\n");
    }
    
}