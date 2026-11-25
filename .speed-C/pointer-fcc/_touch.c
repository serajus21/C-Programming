//_touch.c
/*
    - flags
    - unlimited files
    - prevent fileCreation without extension
    - template if this is .c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int fileCount, char *fileNames[])
{
    for (int fileNames_index = 1; fileNames_index < fileCount; fileNames_index++)
    {
        // version
        if (strcmp(fileNames[1], "-v") == 0 || strcmp(fileNames[1], "--version") == 0)
        {
            puts("_touch version 3.42.4");
            break; // terminates loop
        }
        // help
        if (strcmp(fileNames[1], "-h") == 0 || strcmp(fileNames[1], "--help") == 0)
        {
            puts("_touch <..file..> <..file..> ... ...");
            puts("Existing file will not be created");
            break; // terminates look
        }
        // fileCreation without extension
        if (strchr(fileNames[fileNames_index], '.') == 0)
        {
            printf("%s | Unintended file name\n", fileNames[fileNames_index]);
            continue; // terminates iteration | check next fileName
        }
        // fileCreation
        FILE *file = fopen(fileNames[fileNames_index], "wx");
        // error handling
        if (file == NULL)
        {
            printf("%s already exists\n", fileNames[fileNames_index]);
            continue;
        }
        // template if the file is .c
        int fileName_Length = strlen(fileNames[fileNames_index]);
        if (fileName_Length > 2 &&
            fileNames[fileNames_index][fileName_Length - 2] == '.' &&
            fileNames[fileNames_index][fileName_Length - 1] == 'c')
        {
            fprintf(file,
                    "// %s\n"
                    "#include <stdio.h> \n#include <stdlib.h> \n#include <string.h>\n\n"
                    "int main(void) \n{ \n\n\treturn 0; \n}",
                    fileNames[fileNames_index]);
        }
    }

    return 0;
}