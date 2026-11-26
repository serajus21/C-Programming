// locale.c
// The same number, printed under two locales.
#include <stdio.h>
#include <locale.h>

int main(void) {
    printf("C locale:      %.2f\n", 3.14159);

    if (setlocale(LC_ALL, "de_DE.UTF-8") == NULL) {
        printf("the German locale is not installed\n");
        return 0;
    }
    printf("German locale: %.2f\n", 3.14159);
}
