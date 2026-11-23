/*
 * Chapter 1, Section 1.9 (Phase 6: Execution) - Challenge 2
 * Title: Cargo Manifest Weighing
 *
 * OBJECTIVE
 *   A cargo bay can carry at most 2,000,000,000 grams. Packages are weighed
 *   one by one at the door. Write a program that accepts each package only if
 *   the bay can still carry it, and reports the final tally. A package that
 *   does not fit is turned away; the loading then carries on with the next one.
 *
 * REQUIREMENTS
 *   1. Read package weights (grams), one per line, until a weight of 0 is read
 *      or the input ends, whichever comes first.
 *   2. For every weight, print one line, as shown under "Output format".
 *   3. After the last weight, print the summary line (also when no weight was
 *      read, and also after an invalid-weight message).
 *   4. The program must never accept a package that would make the total
 *      exceed 2,000,000,000, and must never turn away one that would make it
 *      exactly 2,000,000,000.
 *
 * CONSTRAINTS
 *   - Single file, standard C17, only <stdio.h>.
 *   - The running total and each weight are objects of type int. No other
 *     integer or floating type may hold them (a plain int object is all you
 *     get on this bay's controller).
 *   - Your test for "does it fit" must itself be correct for every valid
 *     weight and every possible running total.
 *   - Zero warnings with gcc -std=c17 -Wall -Wextra -Wpedantic.
 *
 * INPUT FORMAT
 *   Integers separated by white space (normally one per line).
 *
 * VALID RANGES
 *   Each weight: 0 .. 2000000000 (0 is the end marker).
 *
 * INVALID INPUT
 *   A weight below 0, above 2000000000, or text that is not an integer:
 *   write  ERROR: invalid weight  (followed by a newline) to the standard
 *   error stream, stop reading, still print the summary line, and terminate
 *   with exit status 1. Otherwise the exit status is 0.
 *
 * OUTPUT FORMAT (standard output)
 *   ACCEPTED <weight> TOTAL <total after this package>
 *   REJECTED <weight> TOTAL <total, unchanged>
 *   SUMMARY accepted=<count> rejected=<count> total=<final total>
 *
 * EDGE CASES TO HANDLE
 *   - a package that brings the total to exactly the capacity
 *   - two packages whose weights add up to more than the largest value an
 *     int can hold
 *   - end of input without a 0
 *   - a 0 as the very first weight
 *
 * ACCEPTANCE CRITERIA
 *   Input (one number per line): 1500000000 1500000000 500000000 0
 *       ACCEPTED 1500000000 TOTAL 1500000000
 *       REJECTED 1500000000 TOTAL 1500000000
 *       ACCEPTED 500000000 TOTAL 2000000000
 *       SUMMARY accepted=2 rejected=1 total=2000000000          status 0
 *   Input: 2000000000 1 0
 *       ACCEPTED 2000000000 TOTAL 2000000000
 *       REJECTED 1 TOTAL 2000000000
 *       SUMMARY accepted=1 rejected=1 total=2000000000          status 0
 *   Input: 100 -5 200
 *       ACCEPTED 100 TOTAL 100
 *       SUMMARY accepted=1 rejected=0 total=100                 status 1
 *       (and ERROR: invalid weight on standard error)
 *   Input: (empty)
 *       SUMMARY accepted=0 rejected=0 total=0                   status 0
 *   Input: 5 7  (then the input ends)
 *       ACCEPTED 5 TOTAL 5
 *       ACCEPTED 7 TOTAL 12
 *       SUMMARY accepted=2 rejected=0 total=12                  status 0
 *
 *   Verification step: also build once with
 *       gcc -std=c17 -g -fsanitize=undefined <file>.c -o cargo
 *   and run the first sample. A clean run supports your answer but does not
 *   prove it for inputs you did not try.
 *
 * WRITTEN ANSWER (put it in a comment at the end of your file, 2-3 sentences)
 *   State the largest value any single arithmetic expression in your
 *   "does it fit" test can take, and why it cannot exceed what an int holds.
 */

#include <stdio.h>

/* ---------------- Your implementation below ---------------- */

