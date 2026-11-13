#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int first = 0;
    int second = 0;

    printf("In the second terminal, run:\n./main %ld %p %p\n", 
           (long)getpid(), (void *)&first, (void *)&second);
    puts("Both integers start at zero.");

    printf("Enter two integers: ");
    fflush(stdout);
    if (scanf("%d %d", &first, &second) != 2) {
        printf("Invalid input. Please enter two integers.\n");
        return 1;
    }

    printf("Sum: %lld\n", (long long)first + second);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
    puts("Variables are still alive. Press Enter to exit.");
    getchar();
    return 0;
}
