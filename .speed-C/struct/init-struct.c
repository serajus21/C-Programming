// init-struct.c
#include <stdio.h>

/* init
struct studentData
{
    int id;
    char section;
};
int main(void) {
    struct studentData serajus;
    serajus.id = 32;
    serajus.section = 'A';

    struct studentData salehin;
    salehin.id = 90;
    salehin.section = 'B';

    printf("ID: %d\n", serajus.id);
    printf("Section: %d\n", serajus.section);
    // printf("Type: %s\n", sizeof(studentData));
}
*/

/*template struct*/
struct Person // user-defined data type
{
    int age;      // member-1
    float salary; // member-2
};

int main(void)
{
    /* tried to form a loop
    struct Person EMP1, EMP2; // variable from user-defined data-type
    // EMP1
    EMP1.age = 23;
    EMP1.salary = 3023.20;
    // EMP2
    EMP2.age = 33;
    EMP2.salary = 3022.42;

    // printf("Employee-1 Age: %d\n", EMP1.age);
    // printf("Employee-1 Salary: %.2f\n", EMP1.salary);

    // for (int i = 1; i < 3; i++)
    // {                                                        // NOT POSSIBLE
    //     printf("Employee-%d Age: %d\n", EMP(i).age);         // operator form
    //     printf("Employee-%d Salary: %.2f\n", EMP[i].salary); // array form
    // }
    return 0;
    */

    /* user-defined data-type | array variable
    struct Person EMP[3];

    EMP[0].age = 23;
    EMP[0].salary = 2000.50;

    EMP[1].age = 45;
    EMP[1].salary = 4000.90;

    EMP[2].age = 42;
    EMP[2].salary = 2323.52;

    int EMP_Length = sizeof(EMP) / sizeof(EMP[0]);

    for(int empIndex=0; empIndex<EMP_Length; empIndex++) {
        printf("Employer-%d Age: %d\n", empIndex+1, EMP[empIndex].age);
        printf("Employer-%d Salary: %.2f\n", empIndex+1, EMP[empIndex].salary);
    }
    */
   
}