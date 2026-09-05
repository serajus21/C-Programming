// cmd-arg.c

#include<stdio.h>
int main(int argc, char *argv[]) {
    for(int i=0; i<argc; i++) {
        if(i==0) {
            return 0;
        } else
        printf("%s\n",argv[i]);
    }
}