// demorgan.c
#include <stdio.h>

int main(void) {
    printf(" a b | !(a&&b)  !a||!b  | !(a||b)  !a&&!b\n");
    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            printf(" %d %d |    %d        %d    |    %d        %d\n",
                   a, b, !(a && b), !a || !b, !(a || b), !a && !b);
        }
    }
}
