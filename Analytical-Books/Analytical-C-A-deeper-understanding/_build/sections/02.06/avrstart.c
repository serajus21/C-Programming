// avrstart.c
// A tiny bare-metal program, to see what runs before main.
#include <stdint.h>

uint8_t counter = 5;            // initialized: its 5 must be copied from flash
uint8_t total;                  // not initialized: must be set to 0

int main(void) {
    total = counter + 1;
    return 0;
}
