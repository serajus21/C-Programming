// file-read-init-cmd.c

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int entryCount, char *entries[]) {
    FILE *file = fopen(entries[1], "r");

    if(file == NULL) {
        puts("We could not access file");
    } else {
        while (!feof(file))
        {
            printf("%c", fgetc(file));
        }
        fclose(file);
    }
}