// _touch.c

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int entryCounts, char *entries[]) {
    
    // entry
    if(entryCounts != 2) {
        puts("_touch [filename.ext]");
        return 1;
    }
    
    FILE *file = fopen(entries[1], "wx");

    if(file == NULL) {
        puts("File Exists already");
        return 1;
    }

    int fileNameLength = strlen(entries[1]); // fileName length | entries[1]
 
    // for .c file
    if(fileNameLength >= 2 && entries[1][fileNameLength-2] == '.' && entries[1][fileNameLength-1] == 'c') {
        fprintf(file, 
            "//%s\n" 
            "#include <stdio.h>\n\n" 
            "int main(void) {\n\n" "}\n", 
            entries[1]);
    }
    // for .py file
    if(fileNameLength >= 3 && entries[1][fileNameLength-3] == '.' && entries[1][fileNameLength-2] == 'p' && entries[1][fileNameLength-1] == 'y') {
        fprintf(file, "#%s\n", entries[1]);
    }

    // if(strcmp(entries[1], "program.c") == 0) {
    //     fprintf(file, "%s \n%s", "#include<stdio.h>", "int main(void) {}");
    // }

    fclose(file);
    return 1;
}