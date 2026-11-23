/*
 * Chapter 1, Section 1.9 (Phase 6: Execution) - Challenge 1
 * Title: Race Pace Reporter
 *
 * OBJECTIVE
 *   A running club records, for each race result, the distance in metres and
 *   the finish time in hours, minutes and seconds. Write a program that reads
 *   one result and reports the runner's average speed and average pace.
 *
 * REQUIREMENTS
 *   1. Print the prompt line exactly as shown under "Acceptance criteria".
 *   2. Read four integers: distance (m), hours, minutes, seconds.
 *   3. Average speed is distance in kilometres divided by time in hours,
 *      printed in km/h with exactly two digits after the decimal point.
 *   4. Average pace is the number of whole seconds needed per kilometre
 *      (any fraction of a second is discarded, not rounded), printed as
 *      minutes and seconds.
 *   5. A result that cannot be processed must never crash the program.
 *      Report it as described under "Invalid input" and stop.
 *
 * CONSTRAINTS
 *   - Single file, standard C17, only <stdio.h>.
 *   - The pace must be computed with int arithmetic; the speed with double.
 *   - The program must compile with
 *         gcc -std=c17 -Wall -Wextra -Wpedantic <file>.c -o race
 *     with zero warnings.
 *
 * INPUT FORMAT
 *   One line: distance hours minutes seconds   (separated by spaces)
 *
 * VALID RANGES
 *   distance : 1 .. 100000        hours   : 0 .. 99
 *   minutes  : 0 .. 59            seconds : 0 .. 59
 *   The total time must be greater than zero.
 *
 * OUTPUT FORMAT (standard output, on success)
 *   Average speed: S km/h
 *   Pace: M min X s per km
 *
 * INVALID INPUT (nothing but the prompt may appear on standard output)
 *   Write exactly one of these lines to the standard error stream, then
 *   terminate with exit status 1. Test the conditions in this order:
 *     fewer than four integers could be read  -> ERROR: input must be four integers
 *     distance outside its range              -> ERROR: distance must be between 1 and 100000 m
 *     hours, minutes or seconds out of range  -> ERROR: time fields out of range
 *     total time equal to zero                -> ERROR: time must be greater than zero
 *   The exit status on success is 0. (The exit status of a program is the
 *   value main returns; a shell shows it with:  echo $?  )
 *
 * Note on writing to standard error: fprintf(stderr, ...) works like printf
 * with one extra first argument naming the stream. It is given here only as a
 * tool; Section 1.9.7 introduces the stream itself, not this function.
 *
 * EDGE CASES TO HANDLE
 *   - distance 0
 *   - total time 0 with a valid distance
 *   - non-numeric input
 *   - the largest valid distance with the largest valid time
 *
 * ACCEPTANCE CRITERIA (standard output, then exit status)
 *   Prompt line, always printed first, followed by a newline:
 *       Enter distance (m), hours, minutes, seconds:
 *
 *   Input "10000 0 48 0"
 *       Average speed: 12.50 km/h
 *       Pace: 4 min 48 s per km                           exit status 0
 *   Input "5000 0 27 13"
 *       Average speed: 11.02 km/h
 *       Pace: 5 min 26 s per km                           exit status 0
 *   Input "100000 99 59 59"
 *       Average speed: 1.00 km/h
 *       Pace: 59 min 59 s per km                          exit status 0
 *   Input "0 1 0 0"      -> stderr: ERROR: distance must be between 1 and 100000 m,  status 1
 *   Input "1000 0 0 0"   -> stderr: ERROR: time must be greater than zero,           status 1
 *   Input "1000 0 60 0"  -> stderr: ERROR: time fields out of range,                  status 1
 *   Input "12 abc"       -> stderr: ERROR: input must be four integers,               status 1
 *
 *   Check each case from the terminal, for example:
 *       echo "0 1 0 0" | ./race ; echo $?
 */

#include <stdio.h>

/* ---------------- Your implementation below ---------------- */

