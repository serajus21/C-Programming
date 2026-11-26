// pragma.c
// Which directives survive -E?
#define GREETING "hello"
#pragma GCC diagnostic ignored "-Wunused-variable"

int main(void) {
    int unused;
    return 0;
}
