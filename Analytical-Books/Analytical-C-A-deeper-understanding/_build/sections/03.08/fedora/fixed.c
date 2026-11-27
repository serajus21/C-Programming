// fixed.c
// Deliberate choices, written so that the compiler need not guess.
#include <stdio.h>

static int next_value(void) { return 5; }

static int rank(char grade) {            // passing grades, counting down
    int n = 0;
    switch (grade) {
    case 'A': ++n; [[fallthrough]];      // C23: the fall-through is intended
    case 'B': ++n; [[fallthrough]];
    case 'C': ++n; break;
    }
    return n;
}

static int first(int x, [[maybe_unused]] int y) {   // y: fixed interface
    return x;
}

int main(void) {
    int v;
    if ((v = next_value()))              // the assignment is intended
        printf("got %d\n", v);
    printf("%d %d\n", rank('A'), first(1, 2));
    return 0;
}
