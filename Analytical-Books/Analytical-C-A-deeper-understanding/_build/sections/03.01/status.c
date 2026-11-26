// status.c
// main's return value becomes the program's exit status.
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;        // no number given
    }
    return atoi(argv[1]);           // return the number typed after the name
}
