// comments.c
// What is, and what is not, a comment.
#include <stdio.h>

int main(void) {
    printf("/* not a comment */\n");      // a comment
    int x = 10 /* a comment */ + 5;        /* also a comment */
    printf("%d\n", x);
    return 0;
}
