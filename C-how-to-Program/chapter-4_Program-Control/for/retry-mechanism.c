// retry-mechanism.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define divider "\n-----------------------------------------------------------------\n"

/*A simulation*/
/*
int main(void)
{
    const int PACKET_COUNT = 3;
    const int MAX_ATTEMPTS = 3;

    // Simulation : attempt number on which each packet succeeds
    // 0 means it never succeeds
    int successOnAttemp[] = {1, 3, 0};

    for (int packet = 0; packet < PACKET_COUNT;)
    {
        int attempts = 0;
        int transmissionSuccessful = 0;
        printf("\nProcessing Packet %d\n", packet);

        while (attempts < MAX_ATTEMPTS && !transmissionSuccessful)
        {
            attempts++;
            printf("Attemp %d: ", attempts);

            // simulated transmission operation
            if (successOnAttemp[packet] != 0 && attempts >= successOnAttemp[packet])
            {
                transmissionSuccessful = 1;
                printf("Transmission successful!\n");
            }
            else
            {
                printf("Transmission failed!\n");
            }
        }

        if (transmissionSuccessful)
        {
            printf("Packet %d delivered successfully.\n", packet);
        }
        else
        {
            printf("Packet %d abandoned after %d attempts.\n", packet, attempts);
        }

        // move to the next packet
        packet++;
    }

    return 0;
}
*/

/*A file opening*/
/*
int main(void)
{
    const int MAX_ATTEMPTS = 3;
    int attempts = 0;
    int fileOpened = 0;
    char fileName[100] = {};
    FILE *file = NULL;

    while (attempts < MAX_ATTEMPTS && !fileOpened) // if file hasn't been opened
    {
        printf("\nEnter the filename to open: ");
        if (fgets(fileName, sizeof fileName, stdin) == NULL)
        {
            printf("Input Error. Cannot continue.\n");
            break;
        }
        fileName[strcspn(fileName, "\n")] == '\0'; // replacing filenames '\n' with string terminator '\0'
        attempts++;
        printf("Attempt %d of %d", attempts, MAX_ATTEMPTS);
        file = fopen(fileName, "r");

        if (file != NULL)
        {
            fileOpened = 1;
            printf("Success ! File '%s' is opened.\n", fileName);
        }
        else
        {
            printf("Failed to open '%s'.\n", fileName);
        }
    }

    if (fileOpened)
    {
        printf("\nThe file is ready for reading\n");
        fclose(file);
    }
    else
    {
        printf("\nCould not open a file after %d attemps.\n", attempts);
        printf("Abandoing this operation.\n");
    }

    puts("\nProgram Finished");
}
*/

int main(void)
{
    int MAX_ATTEMPTS = 3;
    char fileName[100] = {};
    FILE *file = NULL;

    printf("Enter filename: ");
    fgets(fileName, sizeof fileName, stdin);

    for (int attempt = 1; attempt <= MAX_ATTEMPTS;)
    {
        puts("Please while we are searching for your file...");
        sleep(5);

        fileName[strcspn(fileName, "\n")] = '\0';
        file = fopen(fileName, "r");
        if (file != NULL)
        {
            printf("%s opening at attempt %d\n", fileName, attempt);
            puts(divider);
            while (!feof(file))
            {
                printf("%c", fgetc(file));
            }
            puts(divider);
            fclose(file);
            break;
        }
        else
        {
            puts("We could not open file");
        }
        attempt++;
    }

    return 0;
}