//_touch-retouch.c

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "_touch-retouch-header.h"


int main(int fileCount, char *fileEntries[]) 
{

    if(fileCount == 1)
    {
        puts(WARNING);
        return 1;
    }

    for(int fileCounter=1; fileCounter<fileCount; fileCounter++)
    {
        if((strcmp(fileEntries[fileCounter],"--v") == 0) || (strcmp(fileEntries[fileCounter],"-version") == 0))
        {
            puts(VERSION);
            puts(COPYRIGHT);
            puts(DATE);
            break;
        }

        if((strcmp(fileEntries[fileCounter],"--h") == 0) || (strcmp(fileEntries[fileCounter],"-help") == 0))
        {
            puts(USAGE);
            puts(RULE);
            puts(FEATURE);
            break;
        }

        FILE *file = fopen(fileEntries[fileCounter], "wx");

        if(file == NULL)
        {
            puts(_EXIST_WARNING);
            return 1;
        }
        fclose(file);
    }

return 0;
}