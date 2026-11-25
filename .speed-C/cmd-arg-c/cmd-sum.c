//cmd-sum.c

#include<stdio.h>
int main(int argc, char *argv[]) {
    int total = 0;

    for(int index=0; index<argc; index++) {
        total += (int)argv[index];
    }

    printf("Total: %d\n", total);
}