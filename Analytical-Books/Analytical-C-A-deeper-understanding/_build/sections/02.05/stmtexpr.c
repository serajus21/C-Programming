#include <stdio.h>
int main(void) {
    int x = ({ int t = 6; t * 7; });   /* a GNU statement expression */
    switch (x) { case 40 ... 45: puts("in range"); break; }
    return 0;
}
