// majority.c  (Experiment 01.02-2)
#include <stdio.h>

int gate_nand(int a, int b) {
    return !(a && b);
}

int gate_not(int a) {
    return gate_nand(a, a);
}

int gate_and(int a, int b) {
    return gate_not(gate_nand(a, b));
}

int gate_or(int a, int b) {
    return gate_nand(gate_not(a), gate_not(b));
}

int majority(int a, int b, int c) {     // 1 when at least two inputs are 1
    int ab = gate_and(a, b);
    int ac = gate_and(a, c);
    int bc = gate_and(b, c);
    return gate_or(gate_or(ab, ac), bc);
}

int main(void) {
    printf(" a b c | majority\n");
    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            for (int c = 0; c <= 1; ++c) {
                printf(" %d %d %d |    %d\n", a, b, c, majority(a, b, c));
            }
        }
    }
}
