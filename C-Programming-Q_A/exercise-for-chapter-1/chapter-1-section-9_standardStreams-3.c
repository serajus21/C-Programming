/*
 * Chapter 1, Section 1.9 (Section 1.9.7: standard input, output and error) - Challenge 3
 * Title: Order Desk Log Splitter
 *
 * OBJECTIVE
 *   An order desk receives a log of orders, one per line: an order number and
 *   a quantity. A script runs your program on the log so that the good orders
 *   go to one file and the problem reports go to another file, while the
 *   program itself never mentions any file name. Write that program.
 *
 * REQUIREMENTS
 *   1. Read pairs "orderNumber quantity" until the input ends.
 *   2. A pair with quantity 1 .. 1000 is a good order: print
 *          ORDER <orderNumber> QTY <quantity> RUNNING <units so far>
 *      on the standard output stream ("units so far" includes this order).
 *   3. A pair with any other quantity is a rejected order: print
 *          REJECTED ORDER <orderNumber>: quantity <quantity> out of range 1-1000
 *      on the standard error stream, and carry on with the next pair.
 *   4. If the input stops making sense (a pair cannot be read although the
 *      input has not ended, including a last pair that has only its first
 *      number), print  MALFORMED INPUT  on the standard error stream and stop
 *      reading.
 *   5. In every case, finish by printing on the standard output stream
 *          SUMMARY orders=<good orders> units=<total units> rejected=<rejected orders>
 *   6. Exit status: 3 if the input was malformed; otherwise 2 if at least one
 *      order was rejected; otherwise 0.
 *
 * CONSTRAINTS
 *   - Single file, standard C17, only <stdio.h>.
 *   - No prompts, no file names, no opening or closing of files in the program.
 *   - Zero warnings with gcc -std=c17 -Wall -Wextra -Wpedantic.
 *   - Totals are small enough for int (at most 100000 orders per log).
 *
 * Note on writing to standard error: fprintf(stderr, ...) works like printf
 * with one extra first argument naming the stream. It is given here only as a
 * tool; Section 1.9.7 introduces the stream itself, not this function.
 *
 * INPUT FORMAT
 *   Two integers per order, separated by white space (normally one order per
 *   line). The last line may lack a final newline.
 *
 * EDGE CASES TO HANDLE
 *   - an empty log
 *   - a log whose last line has no newline
 *   - a log that ends right after the first number of a pair
 *   - a letter where a number was expected
 *   - quantity exactly 1 and exactly 1000 (both good), 0 and 1001 (both rejected)
 *
 * ACCEPTANCE CRITERIA
 *   Build:  gcc -std=c17 -Wall -Wextra -Wpedantic <file>.c -o desk
 *   Create a file orders.txt (in any scratch folder, not in this exercise
 *   folder) containing:
 *       101 5
 *       102 0
 *       103 12
 *       104 1500
 *       105 3
 *   Run:   ./desk < orders.txt > good.txt 2> bad.txt ; echo $?
 *   Then:
 *     good.txt must contain exactly
 *         ORDER 101 QTY 5 RUNNING 5
 *         ORDER 103 QTY 12 RUNNING 17
 *         ORDER 105 QTY 3 RUNNING 20
 *         SUMMARY orders=3 units=20 rejected=2
 *     bad.txt must contain exactly
 *         REJECTED ORDER 102: quantity 0 out of range 1-1000
 *         REJECTED ORDER 104: quantity 1500 out of range 1-1000
 *     and the printed exit status must be 2.
 *
 *   Log "7 4" then "8 x":
 *       standard output: ORDER 7 QTY 4 RUNNING 4
 *                        SUMMARY orders=1 units=4 rejected=0
 *       standard error : MALFORMED INPUT                         status 3
 *   Empty log:
 *       standard output: SUMMARY orders=0 units=0 rejected=0     status 0
 *   Log "9 1000" then "10 1" then "11" (no newline, input ends):
 *       standard output: ORDER 9 QTY 1000 RUNNING 1000
 *                        ORDER 10 QTY 1 RUNNING 1001
 *                        SUMMARY orders=2 units=1001 rejected=0
 *       standard error : MALFORMED INPUT                         status 3
 *
 *   Also run it with the log arriving through a pipe instead of a file, for
 *   example:  printf '1 5\n2 0\n' | ./desk   and, in a comment at the end of
 *   your file, record in one sentence what appears on the screen and why both
 *   streams show up there when no redirection is used.
 */

#include <stdio.h>

/* ---------------- Your implementation below ---------------- */

