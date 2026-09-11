// simpleMatrix.c
// take values of matrix and print

#include<stdio.h>
int main(void) {
    int matrix[3][4];
    printf("Enter Values for matrix \n");

    //input
    for(int ri=0; ri<3; ri++) {
        for(int ci=0; ci<4; ci++) {
            printf("matrix[%d][%d]: ", ri,ci);
            scanf("%d", &matrix[ri][ci]);
        }
    }

    // print
    printf("%s","matrix[3][4] = \n");
    for(int ri=0; ri<3; ri++) {
        for(int ci=0; ci<4; ci++) {
            printf("%d\t", matrix[ri][ci]);
        }
        puts("");
    }
}