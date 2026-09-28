// file-read-init.c

#include <stdio.h>
#include <string.h>

int main(void)
{
    /* reading from file */
    FILE *_file_read_init_txt = fopen("file-read-init-db.txt", "r");
    char fileChars;

    if (_file_read_init_txt == NULL)
    {
        puts("FILE NOT FOUND");
    }
    else
    {
        puts("Reading File...");
        while (!feof(_file_read_init_txt)) // file "end of file" reading
        {
            fileChars = fgetc(_file_read_init_txt);
            printf("%c", fileChars);
        }
        fclose(_file_read_init_txt);
    }
}