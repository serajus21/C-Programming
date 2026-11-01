// retry-mechanism-2.c
/*
    - we'll attempt to read the content of a file
    - initially file won't be existed; eventually the attempt to openning file will be failed
    - in the middle of program execution we'll create look-up file in another terminal-tab;
    - as we'll get enough inverval through sleep method from unistd library
    - at a random attempt program will find file and show it's content
    - RETRY MECHANISM SUCCESSFULL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define divider "-----------------------------------------"
#define fileDivider "..................................."

int main(void)
{
    int MAX_ATTEMPT = 10;    // maximum attempt | if file couldn't found within this, program will be terminated
    int attempt = 0;         // initializing attempt
    char fileName[100] = {}; // fileName, not file itself, it's just string
    printf("Enter file name your are looking for: ");
    fgets(fileName, sizeof fileName, stdin);
    fileName[strcspn(fileName, "\n")] = '\0'; // fileName's default last characte is \n, it's now replaced by string terminator \0;

    FILE *file = NULL; // file pointer initiated

    for (attempt = 1; attempt <= MAX_ATTEMPT;)
    {
        // inter-iteration interval | waiting for fileName
        printf("Attempt %d in progress...\n", attempt);
        sleep(5);

        file = fopen(fileName, "r"); // file initiated to read-mode

        if (file == NULL) // if file doesn't exist
        {
            puts("Attempt Failed. Retrying.");
        }
        else // if file exists
        {
            puts(fileDivider);
            while (!feof(file)) // read until file's end character
            {
                printf("%c", fgetc(file)); // read entire file char-by-char
            }
            puts("");
            puts(fileDivider);
            puts("\nAttempt Successful."); // confirmation message
            break;
        }

        puts(divider);
        attempt++; // increment in body | directing loop to next iteration
    }

    if(attempt > MAX_ATTEMPT)
    {
        puts("OPERATION UNSUCCESSFULL");
    }

    return 0;
}