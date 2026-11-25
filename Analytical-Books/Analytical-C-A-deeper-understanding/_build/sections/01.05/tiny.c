// tiny.c
// A complete stored-program computer in 32 bytes of memory.
// Each instruction is one byte: the top 3 bits are the operation,
// the low 5 bits are a memory address (0..31).
#include <stdio.h>
#include <stdint.h>

enum { HALT, LOAD, STORE, ADD, SUB, JUMP, JZ, OUT };   // operations 0..7
const char *names[] = {"HALT", "LOAD", "STORE", "ADD",
                       "SUB", "JUMP", "JZ", "OUT"};

uint8_t mem[32] = {             // program and data, side by side
    0x39,   //  0: LOAD  25     acc = sum
    0x78,   //  1: ADD   24     acc = acc + n
    0x59,   //  2: STORE 25     sum = acc
    0x38,   //  3: LOAD  24     acc = n
    0x9A,   //  4: SUB   26     acc = acc - 1
    0x58,   //  5: STORE 24     n = acc
    0xC8,   //  6: JZ    8      if acc == 0, go to 8
    0xA0,   //  7: JUMP  0      otherwise repeat
    0x39,   //  8: LOAD  25     acc = sum
    0xE0,   //  9: OUT          print acc
    0x00,   // 10: HALT
    [24] = 10,                  // n
    [25] = 0,                   // sum
    [26] = 1,                   // the constant 1
};

int main(void) {
    uint8_t pc = 0;             // program counter
    uint8_t ir = 0;             // instruction register
    uint8_t acc = 0;            // accumulator
    long steps = 0;
    int running = 1;

    while (running) {
        ir = mem[pc];                   // FETCH the instruction at pc
        pc = (pc + 1) % 32;             // point to the next one
        int op = ir >> 5;               // DECODE: the top 3 bits...
        int addr = ir & 0x1F;           // ...and the low 5 bits
        if (steps < 9) {
            printf("pc=%2d  ir=0x%02X  %-5s %2d   acc=%3d\n",
                   (pc + 31) % 32, ir, names[op], addr, acc);
        }
        switch (op) {                   // EXECUTE
        case HALT:  running = 0;                     break;
        case LOAD:  acc = mem[addr];                 break;
        case STORE: mem[addr] = acc;                 break;
        case ADD:   acc = acc + mem[addr];           break;
        case SUB:   acc = acc - mem[addr];           break;
        case JUMP:  pc = addr;                       break;
        case JZ:    if (acc == 0) { pc = addr; }     break;
        case OUT:   printf("OUT: %d\n", acc);        break;
        }
        ++steps;
    }
    printf("halted after %ld instructions\n", steps);
}
