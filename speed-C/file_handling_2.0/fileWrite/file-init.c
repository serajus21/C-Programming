// file-init.c
// reading & writing to a file

#include<stdio.h>
#include<string.h>

int main(void) {
    FILE *file;
    char userName[30] = "user: sst21\n";
    char pass[30] = "passkey: hello-world\n";


    file = fopen("file-init.txt", "w");

    if(file==NULL) {
        puts("Could not create file");
    } else {
        puts("File is created successfully");
        fputs(userName, file);
        fputs(pass, file);
        fclose(file);
    }
}