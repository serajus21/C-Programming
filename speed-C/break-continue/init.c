//init.c | for learning break and continue

#include<stdio.h>
int main(void) {
    for(int i=1; i<20; i++) {
        if(i%3 == 0) {
            printf("%d\t", i);
            // break; // program terminates at 3
            continue; // sends program to loop again | Starting Over
        }
        if(i == 10) {
            break;
        }
    }
    puts("");
}