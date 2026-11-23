/*
 * Chapter 1, Section 1.9 (Phases 3, 4 and 5: Compile, Link, Load) - Challenge 4
 * Title: Cable Run Length
 *
 * OBJECTIVE
 *   An electrician marks two points on a floor plan, given as x and y
 *   coordinates in metres, and needs the length of the straight cable between
 *   them. Write the program, then investigate how the finished executable is
 *   put together and record your findings (see "Build report").
 *
 * REQUIREMENTS
 *   1. Print the prompt line shown under "Acceptance criteria".
 *   2. Read four real numbers: x1 y1 x2 y2.
 *   3. Print the straight-line distance between the two points as
 *          Distance: D m
 *      with exactly three digits after the decimal point.
 *   4. Invalid input: write one line to the standard error stream and
 *      terminate with exit status 1 (nothing but the prompt on standard output):
 *          fewer than four numbers could be read -> ERROR: input must be four numbers
 *          any coordinate outside -10000 .. 10000 -> ERROR: coordinate out of range
 *      Exit status on success: 0.
 *
 * CONSTRAINTS
 *   - Single file, standard C17.
 *   - Do not write your own root-finding routine; use what the standard
 *     library provides for the mathematics.
 *   - The first build attempt must be exactly:
 *         gcc -std=c17 -Wall -Wextra -Wpedantic cable.c -o cable
 *     (rename the file or adapt the name as needed). Do not add anything to
 *     that first command in advance and do not use optimisation options.
 *
 * VALID RANGES
 *   Each coordinate: -10000 .. 10000 (real numbers, may have a fraction).
 *
 * EDGE CASES TO HANDLE
 *   - both points identical
 *   - the two opposite corners of the full range
 *   - a coordinate just outside the range
 *
 * ACCEPTANCE CRITERIA (standard output, then exit status)
 *   Prompt line, always printed first, followed by a newline:
 *       Enter x1 y1 x2 y2 (metres):
 *   Input "0 0 3 4"                  -> Distance: 5.000 m            status 0
 *   Input "1.5 2.5 1.5 2.5"          -> Distance: 0.000 m            status 0
 *   Input "-10000 -10000 10000 10000"-> Distance: 28284.271 m        status 0
 *   Input "0 0 10001 0"              -> stderr: ERROR: coordinate out of range, status 1
 *   Input "1 2 3"                    -> stderr: ERROR: input must be four numbers, status 1
 *
 * BUILD REPORT (fill in as a comment at the end of your file; use your own
 * words and the literal text your tools print)
 *   (a) Run your first-attempt command. Which of the six phases reported the
 *       result, and what is the first line of the diagnostic? If the build
 *       succeeded for you, say so and name the option or condition that made
 *       it succeed.
 *   (b) Stop after the compile phase only (produce an object file, no
 *       executable) and confirm that this step succeeds. Using any tool you
 *       choose, show the object file's own record of the symbol that is
 *       missing, and copy that one line. In one sentence: why did the
 *       compiler accept a call to a function whose body is nowhere in your file?
 *   (c) Give the final, working build command, and say which phase needed the
 *       difference between this command and your first attempt.
 *   (d) Run the finished executable under a tool that lists the shared
 *       libraries the loader will map into memory for it. Copy its output
 *       and state which listed library is there only because of what you
 *       told the linker in (c).
 *   (e) Is the machine code of that library inside your executable file? Give
 *       the evidence that supports your answer (for example, a size or a
 *       listing) and say when, relative to the six phases, that code reaches
 *       main memory.
 */

#include <stdio.h>
#include <math.h>

/* ---------------- Your implementation below ---------------- */

