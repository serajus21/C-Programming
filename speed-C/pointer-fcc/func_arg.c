// func_arg.c
// call by reference

#include <stdio.h>
#include <stdlib.h>

/* pointer argument | call by reference
void increment(int *a) // recieves the copy of main's a's address only, not value
{
    *a = (*a) + 1; // goes to main's a's address
                   // changes main's a to 11;
                   // silently gets done and lifetime ends
                   // unlike call-by-value, here's nothing like increment's a; it only has address;
                   // increment just can access main's a's value
    printf("Address of a in increment function: %p\n", &a);
}

int main(void)
{
    int a = 10;
    increment(&a);
    printf("a = %d\n", a);
    printf("Address of a in main function: %p\n", &a);
    return 0;
}
*/

/* using direct int return type
int increment(int a)
{
    return a = (a) + 1;
    printf("Address of a in increment function: %p\n", &a);
}

int main(void)
{
    int a = 10;
    increment(a);
    printf("a = %d\n", a);
    printf("Address of a in main function: %p\n", &a);
    return 0;
}
*/



/* will we get incremented 'a' in main? | call by argument

void increment(int a)
{
    a = a + 1;
    printf("Address of a in increment function: %p\n", &a); // address verification
}

int main(void)
{
    int a = 10;
    increment(a); // main invokes increment() function in stack
                  // value of main's a is copied to increment's a
                  // a is incremented by 1
                  // increment() function is wipped out from stack, and main starts calling printf()
                  // though increment() is wipped out from stack, but it's a variable now occupies space in main memory
                  // so, main's a is defferent from increment's a

    printf("a = %d\n", a); // here still a = 10;
                           // cause, main's a and increment's a are defferent | they are local to their functions

    printf("Address of a in main function: %p\n", &a); // address verification
    return 0;
}
*/


/* function-return-type vs pointer-argument
void calculation(int value, int* sq, int *qb) {
    *sq = value*value;
    *qb = value*value*value;
}

int main(void) {
    int n = 3;
    int sq = 0, qb = 0;
    calculation(n, &sq, &qb);
    printf("sq = %d | qb = %d\n", sq, qb);
}
*/