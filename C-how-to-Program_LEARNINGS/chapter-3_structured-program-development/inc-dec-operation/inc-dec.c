//inc-dec.c
//to observe inc dec behaviour of ++ --

#include<stdio.h>
int main(void) {
    int counter = 5;

    for(int i=1; i<counter; ++i) {
        printf("i = %d\n", i);
    }
}