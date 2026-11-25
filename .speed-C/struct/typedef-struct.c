// typedef-struct.c
#include<stdio.h>

typedef struct
{
    int id;
    char section;
} student;

int main(void)
{
    student salehin; // salehin
    salehin.id = 34;
    salehin.section = 'A';
    student serajus; // serajus
    serajus.id = 33;
    serajus.section = 'B';


    // printf("Salehin | ID: %d, Section: %c\n", salehin.id, salehin.section); // print Salehin
    // printf("Serajus | ID: %d, Section: %c\n", serajus.id, serajus.section); // print Serajus

    
}