// sr_order.c
// Release the latch from S = R = 1, but let one gate react before the other.
#include <stdio.h>

int nor(int a, int b) {
    return !(a || b);
}

int main(void) {
    // Upper gate faster: it computes Q first, then the lower gate uses it.
    int q = 0, qbar = 0;
    q = nor(0, qbar);
    qbar = nor(0, q);
    printf("upper gate first: Q = %d, Q' = %d\n", q, qbar);

    // Lower gate faster: it computes Q' first.
    q = 0;
    qbar = 0;
    qbar = nor(0, q);
    q = nor(0, qbar);
    printf("lower gate first: Q = %d, Q' = %d\n", q, qbar);
}
