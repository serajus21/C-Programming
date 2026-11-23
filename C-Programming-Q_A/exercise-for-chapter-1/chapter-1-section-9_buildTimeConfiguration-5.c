/*
 * Chapter 1, Section 1.9 (Phases 2-6 together) - Challenge 5
 * Title: Cold-Storage Temperature Digest
 *
 * OBJECTIVE
 *   A cold-storage depot logs temperatures in tenths of a degree Celsius
 *   (for example -125 means -12.5 C). Write one program that prints a short
 *   digest of a log. The same unchanged source file is used by two depots:
 *   one wants the digest in degrees Celsius, the other in degrees Fahrenheit.
 *   The unit is decided by how the program is BUILT, not by anything typed at
 *   run time and not by editing the source between builds.
 *
 * REQUIREMENTS
 *   1. Read integer readings (tenths of a degree Celsius) from the standard
 *      input until the input ends. They are separated by white space.
 *   2. A reading from -900 to 600 is valid; any other integer is rejected:
 *      write  REJECTED <reading>: out of range -900..600  to the standard
 *      error stream and continue.
 *   3. A token that is not an integer: write  MALFORMED INPUT  to the standard
 *      error stream and stop reading.
 *   4. If at least one valid reading was seen, print on the standard output:
 *          READINGS: <number of valid readings>
 *          MIN: <lowest valid reading> <unit>
 *          MAX: <highest valid reading> <unit>
 *      Temperatures are printed with exactly one digit after the decimal
 *      point; <unit> is the letter C or the letter F.
 *   5. Fahrenheit = Celsius * 9 / 5 + 32. A temperature must never be printed
 *      as -0.0 in either build.
 *   6. If no valid reading was seen, print nothing on standard output.
 *   7. Exit status: 3 if the input was malformed; otherwise 1 if there was no
 *      valid reading; otherwise 2 if any reading was rejected; otherwise 0.
 *
 * CONSTRAINTS
 *   - Single source file, standard C17, only <stdio.h>.
 *   - Exactly one program text serves both depots. The Celsius build is what
 *     you get with the plain command
 *         gcc -std=c17 -Wall -Wextra -Wpedantic <file>.c -o digest
 *     The Fahrenheit build must be produced from the same file with that
 *     command plus whatever extra argument you need. It must not be possible
 *     for the Celsius build to contain the Fahrenheit conversion at all.
 *   - Zero warnings in both builds.
 *   - Do not ask the user which unit to use and do not read any file.
 *
 * Note on writing to standard error: fprintf(stderr, ...) works like printf
 * with one extra first argument naming the stream. It is given here only as a
 * tool; Section 1.9.7 introduces the stream itself, not this function.
 *
 * EDGE CASES TO HANDLE
 *   - an empty log; a log of only rejected readings
 *   - readings -900 and 600 (valid) and -901 and 601 (rejected)
 *   - the reading -178 in the Fahrenheit build (Celsius * 9 / 5 + 32 is a tiny
 *     negative number there)
 *   - one valid reading only (minimum equals maximum)
 *   - a letter in the middle of the log
 *
 * ACCEPTANCE CRITERIA (standard output; exit status in brackets)
 *   Input "-125 30 -40", Celsius build:
 *       READINGS: 3
 *       MIN: -12.5 C
 *       MAX: 3.0 C                                         [0]
 *   Same input, Fahrenheit build:
 *       READINGS: 3
 *       MIN: 9.5 F
 *       MAX: 37.4 F                                        [0]
 *   Input "-178": Celsius build prints MIN and MAX as -17.8 C; Fahrenheit
 *       build prints MIN and MAX as 0.0 F (READINGS: 1).   [0]
 *   Input "-179", Fahrenheit build: MIN and MAX are -0.2 F.   [0]
 *   Input "-900 600", Fahrenheit build:
 *       READINGS: 2 / MIN: -130.0 F / MAX: 140.0 F          [0]
 *   Input "-125 601 30 -901 x 5", Celsius build:
 *       stderr: REJECTED 601: out of range -900..600
 *               REJECTED -901: out of range -900..600
 *               MALFORMED INPUT
 *       stdout: READINGS: 2 / MIN: -12.5 C / MAX: 3.0 C     [3]
 *   Input "601 -901":  nothing on stdout, two REJECTED lines on stderr [1]
 *   Input "5 700 9": stderr REJECTED 700: out of range -900..600;
 *       stdout (Celsius): READINGS: 2 / MIN: 0.5 C / MAX: 0.9 C   [2]
 *   Empty input: nothing printed anywhere                    [1]
 *
 * BUILD REPORT (fill in as a comment at the end of your file)
 *   (a) The two exact build commands you used.
 *   (b) For each build, the exact command that runs ONLY the preprocessing
 *       phase and writes its output to a file, and one sentence describing, in
 *       terms of what you saw when you compared the two outputs with a
 *       comparison tool, how the two builds differ.
 *   (c) State, for the Celsius build, what the compiler proper (the phase
 *       after preprocessing) receives in place of the Fahrenheit conversion,
 *       and why this means the program has no run-time test of the unit.
 *   (d) Run the Fahrenheit executable on the "-178" input and then explain,
 *       in two sentences, why the value your arithmetic produces for that
 *       input is not the same value as the one the output must show.
 */

#include <stdio.h>

/* ---------------- Your implementation below ---------------- */

