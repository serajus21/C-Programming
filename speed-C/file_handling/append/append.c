//append.c
// learning appending text to a C program

#include<stdio.h>
#include<string.h>

int main(void) {
    char appendix[50] = " | About Fox | ";
    FILE *appendFile = fopen("start.txt", "a");

    if(appendFile == NULL) {
        puts("We could not append to file start.txt");
    } else {
        puts("Appending In Progress...");
        for(int index=0; index < strlen(appendix); index++) {
            fputc(appendix[index], appendFile);
        }
        puts("We successfully appended text to start.txt.");
        fclose(appendFile);
    }

    // char fileContext[200] = fread(appendFile);
}