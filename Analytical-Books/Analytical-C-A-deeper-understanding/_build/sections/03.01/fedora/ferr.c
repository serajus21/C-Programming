#include <stdio.h>
int main(void){ int n=printf("hello, world\n"); int a=ferror(stdout); int f=fflush(stdout); int b=ferror(stdout); fprintf(stderr,"n=%d ferror-before=%d fflush=%d ferror-after=%d\n",n,a,f,b); return 0; }
