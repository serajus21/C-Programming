#include<stdio.h>
int main(void) {
    char grade; printf("Enter grade: "); scanf("%c", &grade);

    switch(grade) {
        case 'A': case 'a': puts("Best"); break;
        case 'B': case 'b': puts("Could be done better"); break;
        case 'C': case 'c': puts("Survived"); break;
        default: puts("Invalid Input");
    }
}