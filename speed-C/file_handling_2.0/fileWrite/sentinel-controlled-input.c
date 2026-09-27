// sentinel-controlled-input.c

#include<stdio.h>
#include<string.h>

int main(void) {
    FILE *_sl_database = fopen("sentinel-controlled-databse.txt", "w");
    _sl_database = fopen("sentinel-controlled-databse.txt", "a");

    if(_sl_database == NULL) {
        puts("Files could not be created");
    } else {
        fprintf(_sl_database, "%-15s%-15s\n", "User Names", "Passkey(s)");
        char sentinelChar = 'y';
        while (sentinelChar == 'y')
        {
            // userData recieve
            char userName[15] = "";
            printf("Enter UserName: "); scanf("%s", &userName);
            char passkey[15] = "";
            printf("Enter passkey: "); scanf("%s", &passkey);
            // user data printing to file
            fprintf(_sl_database, "%-15s%-15s\n", userName, passkey);
            // sentinel ?
            printf("Do you want another user? y/n"); scanf("%s", &sentinelChar);
        }
        puts("Writing to file...");
        puts("Succeed");
        fclose(_sl_database);
    }
}