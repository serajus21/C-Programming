// userInput.c

#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *userData;

    userData = fopen("userData.txt", "w"); // wipping out previous data
    userData = fopen("userData.txt", "a"); // appending data

    char userName[25] = "";
    char passKey[25] = "";

    if (userData == NULL)
    {
        puts("Sorry Could not write to userData.txt");
    }
    else
    {
        puts("Writing to file...");
        // -------------- using puts() ------------------
        // fputs(userName, userData);
        // fputs("\n", userData);
        // fputs(passKey, userData);
        // fputs("\n", userData);
        //----------------- using fprint() ---------------
        fprintf(userData, "%-15s", "User Name");
        fprintf(userData, "%-15s\n", "Passkey");
        for (int userCount = 1; userCount <= 2; userCount++)
        {
            printf("Enter User Name; ");
            scanf("%s", &userName);
            fprintf(userData, "%-15s", userName);
            printf("Enter passkey: ");
            scanf("%s", &passKey);
            fprintf(userData, "%-15s\n", passKey);
        }
        puts("file writing successful !!!");
    }
}