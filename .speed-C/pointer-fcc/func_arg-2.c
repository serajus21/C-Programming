//func_arg-2.c

#include <stdio.h> 
#include <stdlib.h>

int inc(int *address) {
    *address = *address+1;
}

int main(void) {
    int a = 10;
    int *p = &a;
    inc(p);
    printf("%d\n", a);

return 0;
}