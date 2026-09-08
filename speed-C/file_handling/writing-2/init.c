//init.c

#include<stdio.h>
#include<string.h>

int main(void) {
    FILE *myFile = fopen("./text.txt", "w");
    char name[50] = "Serajus Salehin 4.0";

    if(myFile == NULL) {
        printf("We could not create or find text.txt");
    }

    printf("We start writing to your file, text.txt\n");

    // for(int index=0; index<strlen(name); index++) {
    //     fputc(name[index], myFile);
    // }
    fputs(name, myFile);


    printf("text.txt has been created and written\n");
    
}