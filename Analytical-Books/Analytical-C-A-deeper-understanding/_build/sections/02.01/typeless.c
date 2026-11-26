// typeless.c: B's habit, written in modern C
int fetch(int p) {
    return *(int *)p;       // treat a number as an address, as B did
}
