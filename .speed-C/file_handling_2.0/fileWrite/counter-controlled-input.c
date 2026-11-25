//counter-controlled-input.c

#include<stdio.h>
#include<string.h>

int main(void) {
    FILE *_cc_database;
    _cc_database = fopen("counter-controlled-databse.txt", "w");
    _cc_database = fopen("counter-controlled-databse.txt", "a");
    
    // counter input
    int entryCount = 0;
    printf("Enter number of users you have: ");
    scanf("%d", &entryCount);

    //if file creation is unsuccessful
    if(_cc_database == NULL) {
        puts("We could not create file");
    } else {
        //header formating
        fprintf(_cc_database, "%-15s%-15s\n", "Username", "Passkey");
        fprintf(_cc_database, "%-15s%-15s\n", "--------", "-------");
        int counter = 1;
        while (counter <= entryCount)
        {
            char userName[15] = "";
            char passkey[15] = "";
            printf("Enter user %d: ", counter); scanf("%s", &userName);
            printf("Enter passkey for user-%d: ", counter); scanf("%s", &passkey);
            fprintf(_cc_database, "%-15s%-15s\n", userName, passkey);
            counter++;
        }
        puts("Writing to file...");
        puts("Succeed !!!");
        fclose(_cc_database);
    }
}