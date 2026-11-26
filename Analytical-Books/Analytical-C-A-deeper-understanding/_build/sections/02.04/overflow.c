// overflow.c
// One question, asked of a signed and of an unsigned integer.
#include <stdio.h>
#include <limits.h>

int next_is_bigger(int x) {
    int next = x + 1;               // signed: overflow is undefined
    return next > x;
}

int next_is_bigger_u(unsigned x) {
    unsigned next = x + 1;          // unsigned: wraps around to 0, by rule
    return next > x;
}

int main(void) {
    printf("signed:   %d\n", next_is_bigger(INT_MAX));
    printf("unsigned: %d\n", next_is_bigger_u(UINT_MAX));
}
