// sr_latch.c
// Two NOR gates wired in a loop: a circuit that remembers.
#include <stdio.h>

int q = 0;                      // output of the upper NOR gate
int qbar = 1;                   // output of the lower NOR gate

int nor(int a, int b) {
    return !(a || b);
}

// Let both gates respond to the inputs S and R. Each step, both gates
// compute their new outputs from the old ones at the same moment.
// Returns the number of steps taken to settle, or -1 if it never settles.
int settle(int s, int r) {
    for (int step = 0; step < 10; ++step) {
        int new_q = nor(r, qbar);
        int new_qbar = nor(s, q);
        if (new_q == q && new_qbar == qbar) {
            return step;
        }
        q = new_q;
        qbar = new_qbar;
    }
    return -1;
}

int main(void) {
    const int s_in[] = {0, 1, 0, 0, 1, 0, 1, 0};
    const int r_in[] = {0, 0, 0, 1, 0, 0, 1, 0};
    const char *what[] = {"start", "set", "hold", "reset",
                          "set", "hold", "both 1", "release"};
    printf("  event    S R | Q Q' | steps to settle\n");
    for (int k = 0; k < 8; ++k) {
        int steps = settle(s_in[k], r_in[k]);
        printf("  %-8s %d %d | %d %d  | ",
               what[k], s_in[k], r_in[k], q, qbar);
        if (steps >= 0) {
            printf("%d\n", steps);
        } else {
            printf("never settles\n");
        }
    }
}
