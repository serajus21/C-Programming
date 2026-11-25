// file-read-init-db.c

#include<stdio.h>
#include<string.h>

int main(void) {
    /* writing to file
    FILE *database = fopen("file-read-init-db.txt", "w");
    database = fopen("file-read-init-db.txt", "a");

    int studentCount = 0;
    int studentCounter = 1;
    printf("%s", "How many students do you have? ");
    scanf("%d", &studentCount);

    if(database == NULL) {
        puts("Could not create and write to file");
    } else {
        fprintf(database, "%-20s%-20s\n", "Student Name", "Unique ID");
        fprintf(database, "%-20s%-20s\n", "------------", "---------");
        while (studentCounter <= studentCount)
        {
            // receiving data
            char name[20] = "";
            printf("Enter Name of Student_%d: ", studentCounter); scanf("%s", &name);
            char id[20] = "";
            printf("Enter unique id of student_%d: ", studentCounter); scanf("%s", &id);
            // storing data to file
            fprintf(database, "%-20s%-20s\n", name, id);
            // incrementing count
            studentCounter++;
        }
        fclose(database);
        puts("Writing to file...");
        puts("SUCCEED");
    }
    */
}