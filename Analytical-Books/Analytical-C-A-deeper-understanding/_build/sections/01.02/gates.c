// gates.c
// Logic gates as C functions on 0 and 1, all built from NAND alone.
#include <stdio.h>

int gate_nand(int a, int b) {       // the one gate we take as given
    return !(a && b);
}

int gate_not(int a) {               // NOT: tie both NAND inputs together
    return gate_nand(a, a);
}

int gate_and(int a, int b) {        // AND: NAND followed by NOT
    return gate_not(gate_nand(a, b));
}

int gate_or(int a, int b) {         // OR: by De Morgan's law
    return gate_nand(gate_not(a), gate_not(b));
}

int gate_xor(int a, int b) {        // XOR: the classic four-NAND circuit
    int n1 = gate_nand(a, b);
    int n2 = gate_nand(a, n1);
    int n3 = gate_nand(b, n1);
    return gate_nand(n2, n3);
}

int main(void) {
    printf(" a b | NAND NOTa  AND   OR  XOR | a^b\n");
    printf("-----+--------------------------+----\n");
    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            printf(" %d %d | %4d %4d %4d %4d %4d | %3d\n",
                   a, b, gate_nand(a, b), gate_not(a), gate_and(a, b),
                   gate_or(a, b), gate_xor(a, b), a ^ b);
        }
    }
}
