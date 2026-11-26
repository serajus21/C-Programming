// greet.c
// A function that is declared but never defined.
void greet(void);       // a declaration: "greet exists somewhere"

int main(void) {
    greet();
    return 0;
}
