// cascade.c
// One missing character, how many messages?
#include <stdio.h>

struct point {
    int x;
    int y;
}                       // the ';' that ends the declaration is missing

int main(void) {
    struct point p = {1, 2};
    printf("%d\n", p.x + p.y);
    return 0;
}
