// init.c of file_handling
// learning how to deal with file
/*
fputc()         fgetc()
fputw()         fgetw()
fputs()         fgets()
fprintf()       fscanf()
fwrite()        fread()
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *file; // file pointer declaration
    char name[200] = "SERAJUS SALEHIN TANZIM";
    int nameLength = strlen(name);

    file = fopen("text.txt", "w"); // file-name, action(w-write,r-read)

    if (file == NULL)
    {
        puts("File does not exist.");
    }
    else
    {
        puts("File is opened");
        for(int i=0; i<nameLength; i++) {
            fputc(name[i],file);
        }
        puts("File is successfully written");
        fclose(file);
    }
}