// p_to_p.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 5;

    int *p = &x; // pointing p to x
    *p = 6;      // dereferencing p to modify x's value to 6; now, x = 6;

    int **q = &p;  // q is pointing to p, p is pointing to x; q=>p pointer-to-pointer
    int ***r = &q; // r=>q=>p | pointer-pointer-pointer | r can never point to p
                   // (*** can't point to *) | *** => ** => * | must maintain chain of command

    printf("%d\n", *p);                                                       // 6
    printf("Address of x |  %p (*q) = %p p(&x)\n", *q, p);                    //*q points to p's value; so it'll print address stored in p, which is address of x;
    printf("*(*q) = %d | value_of_x, value_of_*p, value of *(*q) \n", *(*q)); //*q points to p's value (x's memory address),
                                                                              // *(*q) points to one step ahead, takes p's value (x's memory), go to there, extract 4-bytes of x's value

    printf("x\'s memory address | *(*r)_%p = p(&x)_%p\n", *(*r), p); // r points to q's memory address | *r = p's memory address
                                                                     // **r one step ahead, points to p (x's memory address) | **r = x's memory address
    printf("Value of x | *(*(*r))_%d = x_%d\n", *(*(*r)), x);        // *(*(*r)) goes beyond **r which already has x's memory address, ***r extracts 4 bytes of x value

    ***r = 10; // dereferencing r to modify x's value to 10; now, x = 10;
    printf("x | ***r = %d\n", ***r);

    **q = *p + 2; // q holds p's address, p holds x's address | **q = value of x, which is now 10;
                  // as x is now 10; p is pointing to x'a address, so, *p = 10 = x;
                  // so, **q = *p + 2;
                  // **q = 10+2 = 12;
    printf("%d = *p + 2 \n", **q);
    return 0;
}