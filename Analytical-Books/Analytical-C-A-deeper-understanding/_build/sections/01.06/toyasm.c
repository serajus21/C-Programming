// toyasm.c
// A two-pass assembler for the toy computer of §01.05.
// It turns lines such as "loop: ADD n" into the bytes of Figure 01.05-1.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *source[] = {        // the program, as a person writes it
    "loop:  LOAD  sum",
    "       ADD   n",
    "       STORE sum",
    "       LOAD  n",
    "       SUB   one",
    "       STORE n",
    "       JZ    done",
    "       JUMP  loop",
    "done:  LOAD  sum",
    "       OUT",
    "       HALT",
    "       ORG   24",          // place what follows at address 24
    "n:     DATA  10",
    "sum:   DATA  0",
    "one:   DATA  1",
};
const int nlines = sizeof source / sizeof source[0];

const char *ops[] = {"HALT", "LOAD", "STORE", "ADD",
                     "SUB", "JUMP", "JZ", "OUT"};

char sym_name[32][16];          // the symbol table: names...
int sym_addr[32];               // ...and the addresses they stand for
int nsyms = 0;

int lookup(const char *name) {  // address of a label, or -1
    for (int i = 0; i < nsyms; ++i) {
        if (strcmp(sym_name[i], name) == 0) { return sym_addr[i]; }
    }
    return -1;
}

// Split a line into label, mnemonic and operand; any may be empty.
void split(const char *line, char *label, char *mnem, char *operand) {
    char buf[64];
    strcpy(buf, line);
    label[0] = mnem[0] = operand[0] = '\0';
    char *rest = buf;
    char *colon = strchr(buf, ':');
    if (colon != NULL) {
        *colon = '\0';
        sscanf(buf, "%15s", label);
        rest = colon + 1;
    }
    sscanf(rest, "%15s %15s", mnem, operand);
}

int main(void) {
    char label[16], mnem[16], operand[16];

    // Pass 1: walk the program, noting the address of every label.
    int addr = 0;
    for (int i = 0; i < nlines; ++i) {
        split(source[i], label, mnem, operand);
        if (strcmp(mnem, "ORG") == 0) { addr = atoi(operand); continue; }
        if (label[0] != '\0') {
            strcpy(sym_name[nsyms], label);
            sym_addr[nsyms++] = addr;
        }
        ++addr;                     // every other line fills one byte
    }

    // Pass 2: walk it again, translating each line into a byte.
    addr = 0;
    for (int i = 0; i < nlines; ++i) {
        split(source[i], label, mnem, operand);
        if (strcmp(mnem, "ORG") == 0) { addr = atoi(operand); continue; }
        int byte = -1;
        if (strcmp(mnem, "DATA") == 0) {
            byte = atoi(operand);
        } else {
            for (int op = 0; op < 8; ++op) {
                if (strcmp(mnem, ops[op]) == 0) {
                    int target = operand[0] ? lookup(operand) : 0;
                    if (target < 0) {
                        printf("line %d: unknown label '%s'\n", i + 1,
                               operand);
                        return 1;
                    }
                    byte = (op << 5) | target;  // opcode, then address
                }
            }
        }
        if (byte < 0) {
            printf("line %d: unknown operation '%s'\n", i + 1, mnem);
            return 1;
        }
        printf("%2d: 0x%02X   %s\n", addr, byte, source[i]);
        ++addr;
    }
}
