// struct.c

#include <stdio.h>
#include <string.h>
/* init
struct studentData
{
    int id;
    char section;
};
int main(void)
{

    individual data
    struct studentData Serajus;
    Serajus.id = 222;
    Serajus.section = 'S';

    struct studentData Salehin;
    Salehin.id = 223;
    Salehin.section = 'T';

    printf("About Serajus \t Batch_%d Section_%c\n", Serajus.id, Serajus.section);
    printf("About Salehin \t Batch_%d Section_%c\n", Salehin.id, Salehin.section);
    puts("");


    // array of studentData

}
*/

/* struct with string output;
struct Player {
    char name[20];
    int score;
};

int main(void) {
    struct Player player1;
    struct Player player2;

    strcpy(player1.name, "Serajus");
    player1.score = 4;

    strcpy(player2.name, "Salehin");
    player2.score = 5;

    printf("%-10s\t%-10s\n", "Name", "Score");
    printf("%-10s\t%-10s\n", "----------", "----------");
    printf("%-10s\t%-10d\n", player1.name, player1.score);
    printf("%-10s\t%-10d\n", player2.name, player2.score);
}
*/

// struct with string I/O
struct students
{
    char name[17];
    char name_1[4];  
    int age;
};

int main(void)
{
    struct students st1;
    struct students st2;

    /* this I/O part works
    // printf("%s", "Enter Student-1 Name: ");
    // scanf("%s", &st1.name);
    // printf("%s", "Enter student-1 age: ");
    // scanf("%s", &st1.age);
    */

    /* this static part doesn't work
    // st1.name = "Serajus";
    // st1.age = 32;
    */

    /* this static part works
    // strcpy(st1.name, "Serajus");
    // st1.age = 21;
    */

    // printf("Name: %s | Age: %d\n", st1.name, st1.age);
    printf("%d\n", sizeof(struct students));
}