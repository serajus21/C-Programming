// cmd-sum-fixed.c

#include <errno.h>   // Gives us errno and ERANGE for conversion-error checks.
#include <limits.h>  // Defines INT_MIN and INT_MAX, the limits of an int.
#include <stdio.h>   // Gives us printf.
#include <stdlib.h>  // Gives us strtol, which converts text to a number.

int main(int argc, char *argv[]) {
    /*
     * argc is the number of command-line arguments.
     *
     * argv is an array of strings. For this command:
     *
     *     ./cmd-sum-fixed 4 3
     *
     * argv[0] is "./cmd-sum-fixed"
     * argv[1] is "4"
     * argv[2] is "3"
     *
     * Notice that "4" and "3" are text strings. strtol will convert
     * those strings to real numeric values before we add them.
     */
    int total = 0;

    /*
     * argc includes argv[0], the program name. Therefore argc < 2 means
     * the user gave no numbers at all, for example: ./cmd-sum-fixed
     */
    if (argc < 2) {
        printf("Usage: %s NUMBER [NUMBER ...]\n", argv[0]);
        return 1; // A non-zero return value tells the shell that the program failed.
    }

    /*
     * Start at index 1, not 0, because argv[0] is the program name.
     * The condition index < argc prevents us from accessing past the
     * last element of the argv array.
     */
    for (int index = 1; index < argc; index++) {
        /*
         * strtol writes into end. After conversion, end points to the
         * first character that strtol could not treat as part of a number.
         */
        char *end;

        /*
         * errno is a global error indicator used by some library functions.
         * Set it to zero before strtol so ERANGE afterward can only mean
         * this particular conversion was outside the representable range.
         */
        errno = 0;

        /*
         * Convert the current argument from decimal text to a long.
         *
         * argv[index] = "4"  -->  converted = 4
         * argv[index] = "-12" -->  converted = -12
         *
         * The final 10 says that input is base 10 (ordinary decimal).
         */
        long converted = strtol(argv[index], &end, 10);

        /*
         * Reject bad input:
         *
         * *argv[index] == '\0'  : an empty string, ""
         * *end != '\0'          : unparsed characters remain, e.g. "4abc"
         * errno == ERANGE        : the number is too large or too small
         * converted outside int  : it fits in long but not in int
         */
        if (*argv[index] == '\0' ||
            *end != '\0' ||
            errno == ERANGE ||
            converted < INT_MIN ||
            converted > INT_MAX) {
            printf("Error: \"%s\" is not a valid integer.\n", argv[index]);
            return 1;
        }

        /*
         * This cast is safe because the checks above proved that converted
         * lies between INT_MIN and INT_MAX. It converts a numeric long to
         * a numeric int; it is not trying to convert a string or pointer.
         */
        int number = (int)converted;

        // Add this valid numeric argument to the running total.
        total += number;
    }

    // All arguments were valid, so display their sum.
    printf("Total: %d\n", total);
    return 0; // Zero tells the shell that the program completed successfully.
}
