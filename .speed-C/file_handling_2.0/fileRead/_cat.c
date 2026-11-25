// ccat.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int entryCounts, char *entries[])
{
    FILE *file = fopen(entries[1], "r");

    if(file == NULL) {
        puts("We could not access your file");
    } else {
        while (!feof(file))
        {
            printf("%c", fgetc(file));
        }
        fclose(file);
        puts("");
    }
}