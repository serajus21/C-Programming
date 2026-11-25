//creating-writing-to-a-file.c

#include<stdio.h>
#include<string.h>

int main(void) {
    char name[200] = "Serajus Salehin | 25 | BD";
    FILE *myFile = fopen("myFile.txt", "w");

    //writing to myFile.txt
    // fputc(name, myFile);
    if(myFile == NULL) {
        puts("We couldn\'nt write to myFile.txt");
    } else {
        int nameLength = strlen(name);
        for(int i=0; i<nameLength; i++) {
            fputc(name[i], myFile);
        }
        puts("File has written successfully");
        fclose(myFile);
    }
}