// pointer.c
// pointer practice

#include <stdio.h>
int main(void)
{
    int age = 25;
    int *pAge = &age;
    // pAge => get me value of &age
    // *pAge => get me value of what is stored in &age

    printf("age => %d\n", age);     // 25
    printf("*pAge => %d\n", *pAge); // 25
    printf("&age = %p\n", &age);
    printf("pAge = %p\n", pAge);
}