#include<stdio.h>
int main(void) {
    int i=0;
    printf("main %p\t%p\n", &i, __builtin_frame_address(0));
}