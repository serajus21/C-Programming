---
title: "Analytical C : A deeper understanding"
subtitle: "Table of Contents — Draft v1 (for discussion, not yet approved)"
date: "24 November 2026"
---

# How to read this draft

**Status.** This is a proposal for discussion. Once you approve it (with whatever changes we agree), it becomes `_index.docx`, together with the house style and the revision log.

**Numbering.** Every section has a fixed reference, **§CC.SS** (chapter, section), used for cross-references throughout the book. Each section will become one file, for example `16-Iteration-03-Floating-Point-Control-Variables.docx`.

**"Builds on".** Each section lists the earlier sections it depends on, so the order of dependence is visible and can be checked.

**Sub-topics.** The bullets under each section are the branches that section must explore. They show its scope; they are not its final headings. Facts named here (version numbers, dates, behaviours) are subjects to be *verified* when the section is written, not claims already settled.

## The language baseline

- **Primary baseline: modern C as your Fedora compiler sees it.** GCC 15 compiles C as `-std=gnu23` by default, so the book teaches C23. It uses `-std=c23 -pedantic` when strict standard behaviour is the point, and marks each place where C99, C11 or C17 differed.
- **Embedded baseline: two toolchains, compared honestly.**
  - The Arduino IDE ships its own, older `avr-gcc` (7.3.0). That version's default dialect is GNU C11, and sketches are compiled as C++ (`gnu++11`).
  - Fedora packages a current `avr-gcc` (the 15.x series on recent releases).
  - Bare-metal work in this book uses Fedora's toolchain. Where the same source is judged differently by the two toolchains, the book shows the difference.
- **Three machines throughout:**
  - x86-64 Linux, your laptop;
  - AVR ATmega328P, an 8-bit chip with 16-bit `int`, 2 KB of RAM and no hardware divide;
  - ESP32, a 32-bit Xtensa chip that runs FreeRTOS.

  Seeing one C program on three very different machines is what separates the language from any one implementation of it.

## The anatomy of every section

1. **Builds on**: the sections it rests on.
2. **The question**: the problem or puzzle that makes the topic necessary, usually met through an experiment.
3. **The journey**: the narrative, from intuition to mechanism to the precise rule.
4. **Recurring boxes**, used where they apply: *Why this exists* · *Under the hood* · *Common misconception* · *Precisely speaking* (exactly what the standard says, and which version) · *History* · *On the metal (AVR/ESP32)* · *In orbit* (space-systems relevance).
5. **Self-check**: questions, with answers at the end of the section.
6. **Experiments**: change, predict, run, explain. These use `gcc -E/-S/-c`, `nm`, `objdump`, `gdb`, sanitizers, and the AVR toolchain.
7. **Hands-on (AVR/ESP32)**, where the topic touches hardware.

# Chapter 00 — Before the Journey

### §00.01 How This Book Teaches
Builds on: —

- Why this book exists, and how it differs from a reference manual.
- The method: question → experiment → mechanism → precise rule → connection.
- How claims are labelled: established fact, standard text, implementation behaviour, and the author's inference.
- How to use the experiments, self-checks and boxes; notation and conventions.
- How to study it by hand: what to copy, what to sketch, what to run.

### §00.02 Setting Up the Workbench on Fedora
Builds on: §00.01

- What each tool is for: `gcc`, `gdb`, `make`, `binutils` (`nm`, `objdump`, `readelf`), `valgrind`.
- VS Code as a text editor and terminal, and why the book builds from the command line rather than with a "Run" button.
- The flags the book uses (`-std=c23 -Wall -Wextra -pedantic -g`) and what each one changes.
- The AVR toolchain (`avr-gcc`, `avr-libc`, `avrdude`) and the ESP32 toolchain (ESP-IDF), installed lightly on an 8 GB machine.
- Checking versions, and why the version matters (`gcc --version`, `__STDC_VERSION__`).

# PART I — THE MACHINE BENEATH C

# Chapter 01 — What a Computer Physically Is

### §01.01 Information as Physical States
Builds on: §00.01

- Why a computer stores information as voltages, and why two states (noise margins and reliability).
- The bit as a choice between two states; bytes and words.
- The real voltage levels on the ATmega328P's 5 V logic.
- History: decimal machines (ENIAC) against binary machines, and why binary won.
- In orbit: why the physical nature of a bit makes radiation a threat.

### §01.02 Switches That Compute: From Transistors to Logic
Builds on: §01.01

- The transistor (MOSFET) as a voltage-controlled switch, explained intuitively.
- Building NOT, AND, OR, NAND and NOR from switches.
- Truth tables and Boolean algebra: Boole (1854), and Shannon (1937), who showed that switching circuits obey it.
- Why NAND alone can build everything (universality).
- Combinational logic: outputs that depend only on the present inputs.

### §01.03 Building Arithmetic from Logic
Builds on: §01.02

- Adding binary digits by hand, then by gates: the half adder and the full adder.
- Ripple-carry adders and why their delay matters.
- Subtraction with the same adder (a preview of two's complement).
- The ALU, and the status flags it produces: carry, zero, negative, overflow.
- On the metal: the AVR status register (SREG).

### §01.04 Remembering: Latches, Registers and Memory
Builds on: §01.02

- Feedback creates memory: the SR latch, D latch and flip-flop; the clock.
- Registers as rows of flip-flops.
- Memory arrays: how an address, as a pattern of wires, selects one cell (address decoding).
- SRAM, flash and EEPROM: how each physically holds a bit, and the ATmega328P's 32 KB / 2 KB / 1 KB.
- Volatile against non-volatile storage; in orbit: single-event upsets in memory.

### §01.05 The Stored-Program Machine
Builds on: §01.03, §01.04

- Instructions as numbers held in memory.
- The fetch–decode–execute cycle; the program counter and the instruction register.
- Von Neumann against Harvard architecture, and why the AVR is a (modified) Harvard machine.
- The instruction set architecture (ISA) as a contract between hardware and software.
- Three ISAs used in this book: AVR, x86-64 and Xtensa.

### §01.06 Machine Code and Assembly Language
Builds on: §01.05

- Encoding a real AVR instruction (e.g. `LDI`, `ADD`) bit by bit.
- The assembler as a translator of names into numbers.
- Writing a tiny AVR program in assembly.
- Why assembly ties a program to one machine, and the cost of that.
- The problem that high-level languages were invented to solve.

# Chapter 02 — Why C Exists

### §02.01 The Road to C
Builds on: §01.06

- The first high-level languages (FORTRAN, COBOL, ALGOL) and what they could not do.
- BCPL (Richards, 1967) and B (Thompson, 1969): typeless languages, and why that failed on byte-addressed machines.
- C at Bell Labs (Ritchie, early 1970s), and Unix rewritten in C (1973).
- Portability: one program for many machines.
- How C came to underlie operating systems, firmware and other languages.

### §02.02 The Design Philosophy of C
Builds on: §02.01

- "Close to the machine, yet portable": what that demands of a language.
- Trusting the programmer: no bounds checks and no garbage collector, and the price paid for that.
- A small language with a separate library.
- What C deliberately leaves to the implementation, and why.
- C's strengths and weaknesses for spacecraft and embedded systems.

### §02.03 The C Abstract Machine
Builds on: §02.02

- The standard does not describe your CPU; it describes an *abstract machine*.
- Observable behaviour, and the "as-if" rule.
- Why this gives compilers the freedom to optimize.
- The gap between "what C means" and "what the CPU does", and how to reason across it.

### §02.04 Four Kinds of Behaviour
Builds on: §02.03

- Defined, implementation-defined, unspecified and undefined behaviour, plus locale-specific behaviour.
- Why undefined behaviour exists: the diversity of hardware, and room for optimization.
- First examples, which return later in the book in depth.
- Where to find an implementation's choices (the GCC manual, the ABI documents).
- The engineer's habit: always asking "which kind of behaviour is this?"

### §02.05 Standards and Dialects: K&R to C23
Builds on: §02.04

- K&R (1978), C89/C90, C95, C99, C11, C17 and C23: what each changed, and why.
- GNU dialects and extensions (`gnu11`, `gnu17`, `gnu23`).
- Compiler defaults over time, and why your laptop and the Arduino IDE disagree.
- Checking `__STDC_VERSION__` in a program.
- The book's baseline, and how it marks the differences between versions.

### §02.06 Hosted and Freestanding Implementations
Builds on: §02.05

- With an operating system, and without one: what changes.
- The library a freestanding implementation must still provide.
- `__STDC_HOSTED__`.
- The meaning of `main` on Linux, on a bare ATmega328P, and under ESP-IDF/FreeRTOS.
- Why "the program starts at `main`" is only a convenient simplification.

# Chapter 03 — From Source Text to Running Program

### §03.01 The First Program, Dissected
Builds on: §02.06, §00.02

- Every token of a "hello" program explained: `#include`, `int main(void)`, braces, the call, the string literal, the statement and the return.
- Why `main` returns `int`, and to whom.
- Whitespace, comments and layout: what the compiler ignores, and why humans need them.
- What the program does *not* show: the startup code before it and the library code after it.

### §03.02 The Phases of Translation
Builds on: §03.01

- From characters to tokens to syntax to meaning: the standard's phases of translation, explained intuitively.
- The `gcc` *driver* and the separate programs it runs (`cpp`, `cc1`, `as`, `ld`), seen with `-v`.
- Stopping at each stage with `-E`, `-S` and `-c`.

### §03.03 Preprocessing: Text Before Language
Builds on: §03.02

- What `#include` physically does: pasting text into the file.
- Looking at the result with `gcc -E`.
- A header (declarations) against a library (definitions); correcting the common confusion between the two.
- A first look at macros (treated fully in Chapter 22).

### §03.04 Compiling: From C to Assembly
Builds on: §03.03, §01.06

- Reading `gcc -S` output on x86-64: registers, instructions and the call to `printf`.
- The same source through `avr-gcc -S`.
- How optimization levels (`-O0`, `-O2`, `-Os`) change the output.
- The compiler as a translator that must preserve observable behaviour.

### §03.05 Assembling: Object Files
Builds on: §03.04

- What an object file contains: ELF sections (`.text`, `.data`, `.bss`, `.rodata`), the symbol table and relocations.
- Inspecting object files with `nm`, `objdump` and `readelf`.
- Why an object file is not yet a program.

### §03.06 Linking: Completing the Program
Builds on: §03.05

- Resolving symbols: how the call to `printf` finds its code.
- The C library, the startup files (`crt1.o` and others), and `-lm`.
- Link order, and testing a famous textbook command (`gcc -lm file.c`).
- Static against dynamic linking, at a first glance (`ldd`).

### §03.07 Loading and Running
Builds on: §03.06

- `execve`, the loader, and `_start` → `__libc_start_main` → `main`.
- Where `main`'s return value goes: the exit status, seen as `$?` in the shell.
- The same journey on the AVR: reset vector → `.data` copy → `.bss` clear → `main`.
- What happens when `main` returns on a microcontroller.

### §03.08 Diagnostics: Listening to the Compiler
Builds on: §03.07

- Errors against warnings, and what each means.
- Reading GCC's messages precisely.
- `-Wall`, `-Wextra`, `-pedantic` and `-Werror`.
- Warnings as the earliest bug detector; the warning-free discipline.

# PART II — DATA: HOW C SEES BITS

# Chapter 04 — Numbers as Patterns of Bits

### §04.01 Positional Notation from First Principles
Builds on: §01.01

- What a "digit in a place" means: place values in base 10.
- Base 2, and converting between bases (repeated division; place-value sums).
- Why hexadecimal and octal exist: grouping bits for human eyes.
- Fluency in reading hex.

### §04.02 Unsigned Integers and Modular Arithmetic
Builds on: §04.01, §01.03

- *n* bits give 2ⁿ values.
- The odometer model of wraparound.
- Arithmetic modulo 2ⁿ, and the carry flag.
- Why C defines unsigned wraparound exactly.

### §04.03 Representing Negative Numbers
Builds on: §04.02

- Sign-magnitude and ones' complement, and the problem of two zeros.
- Two's complement: why it won (the same adder does both jobs); negation as "invert and add one".
- The asymmetric range: why −128 has no positive partner.
- History: machines that used ones' complement.
- C23 now mandates two's complement; what earlier standards allowed.

### §04.04 Signed Overflow: Where Hardware and C Part Ways
Builds on: §04.03, §02.04

- The hardware's overflow flag, set against C's undefined behaviour.
- Why C made signed overflow undefined.
- How optimizers exploit it, shown with a loop example.
- The compiler options `-fwrapv` and `-ftrapv`, and the undefined-behaviour sanitizer.
- Checked arithmetic in C23 (`<stdckdint.h>`: `ckd_add` and related macros).

### §04.05 Width, Sign Extension and Truncation
Builds on: §04.04

- Widening signed and unsigned values: sign extension against zero extension.
- Narrowing: what happens to the bits that do not fit.
- Watching the bits with experiments.

# Chapter 05 — C's Integer Types

### §05.01 Why C Has So Many Integer Types
Builds on: §04.05, §02.02

- Matching the hardware's word sizes; the PDP-11 legacy.
- The standard guarantees minimum ranges, not exact sizes.
- The ordering of sizes: `char` ≤ `short` ≤ `int` ≤ `long` ≤ `long long`.

### §05.02 char: The Byte and Its Three Faces
Builds on: §05.01

- `char`, `signed char` and `unsigned char`.
- `CHAR_BIT`, and what "byte" means in C.
- The signedness of plain `char` is implementation-defined, and differs between platforms.

### §05.03 short, int, long and long long Across Machines
Builds on: §05.02

- The LP64 model on x86-64 Linux.
- 16-bit `int` on the AVR; 32-bit on the ESP32.
- `<limits.h>`.
- Experiment: printing the sizes on all three machines.

### §05.04 Exact-Width, Fast and Special-Purpose Types
Builds on: §05.03

- `<stdint.h>`: `uint8_t`, `int32_t`, the `fast` and `least` types, `intptr_t`.
- `size_t` and `ptrdiff_t`.
- Printing them with the `<inttypes.h>` macros.
- `_BitInt(N)` (C23).
- Why embedded code is written with exact-width types.

### §05.05 bool: Truth Becomes a Type
Builds on: §05.04

- From `int` used as truth, to `_Bool` (C99), to `bool` as a keyword (C23).
- What happens when other values are converted to `bool`.

### §05.06 Integer Constants
Builds on: §05.05

- Decimal, octal, hexadecimal and binary (C23) literals.
- The suffixes `U`, `L` and `LL`, and the rule that decides a literal's type.
- C23 digit separators (`'`).
- The leading-zero octal trap.
- Why a character constant such as `'A'` has type `int`.

# Chapter 06 — Objects, Variables and Memory

### §06.01 What a Variable Really Is
Builds on: §05.06, §01.04

- An *object* as a region of storage, with a name, type, value, address and lifetime.
- The rules for identifiers.
- Declaration, definition and initialization, carefully distinguished.

### §06.02 Types as Interpretations of Bits
Builds on: §06.01

- The same bits read as different values.
- What a type decides: the size, the operations allowed, and the meaning of the bits.
- The `sizeof` operator: evaluated at compile time, with result type `size_t`.

### §06.03 Addresses and Byte Order
Builds on: §06.02

- Memory as numbered bytes; the `&` operator and the `%p` conversion.
- Multi-byte objects, and little-endian against big-endian byte order.
- Viewing the bytes of an object through `unsigned char`.
- Network byte order.

### §06.04 Alignment
Builds on: §06.03

- Why hardware prefers aligned access.
- `alignof` and `alignas`.
- The cost of misaligned access on different CPUs; a preview of padding.

### §06.05 Initial and Indeterminate Values
Builds on: §06.04

- What an uninitialized automatic variable contains.
- Why static objects start at zero (and how the `.bss` section achieves it).
- The danger of reading indeterminate values.
- C23's empty initializer `{}`.

### §06.06 Constants: const and constexpr
Builds on: §06.05

- Read-only objects with `const`, and where they live (`.rodata`, and the AVR's surprise).
- `constexpr` objects (C23).
- Literals against named constants.

# Chapter 07 — Floating-Point Numbers

### §07.01 Why Floating Point Exists
Builds on: §04.01

- The range problem: integers cannot hold both 10⁻²⁰ and 10²⁰.
- Scientific notation as a model.
- Trading precision for range.
- History: from Zuse to Kahan and IEEE 754 (1985).

### §07.02 Binary Fractions
Builds on: §07.01

- Place values ½, ¼, ⅛ and so on.
- Converting decimal fractions to binary by repeated doubling.
- Why 0.1 and 0.05 repeat forever in binary.
- Which values are exactly representable.

### §07.03 The Anatomy of IEEE 754
Builds on: §07.02

- Sign, biased exponent, and a significand with a hidden bit.
- The binary32 and binary64 formats.
- Decoding a `float` by hand.
- Experiment: extracting the bits safely with `memcpy`.

### §07.04 Rounding, Precision and Epsilon
Builds on: §07.03

- Round-to-nearest-even.
- The ULP (unit in the last place) and machine epsilon.
- What "about 7 significant digits" really means.
- `<float.h>`.

### §07.05 Zero, Infinity, NaN and Subnormals
Builds on: §07.04

- Signed zero, and infinities.
- NaN, and why `NaN != NaN`.
- Gradual underflow (subnormal numbers).
- Floating-point exceptions (`<fenv.h>`).

### §07.06 When Arithmetic Betrays Mathematics
Builds on: §07.05

- Floating-point addition is not associative.
- Catastrophic cancellation, and the accumulation of error.
- Comparing floating-point numbers: absolute and relative tolerances.
- Kahan summation.

### §07.07 float, double and long double in C
Builds on: §07.06, §05.06

- The type of a literal: `0.05` is a `double`, `0.05f` is a `float`.
- `FLT_EVAL_METHOD`.
- The x86 80-bit extended format behind `long double`.
- `double` on avr-gcc (32-bit by default, with an option for 64-bit — to be verified).
- The ESP32's single-precision FPU, and the cost of software floating point.

### §07.08 Fixed-Point Arithmetic
Builds on: §07.07

- Computing with fractions on CPUs that have no FPU.
- Q formats, and scaled integers.
- Money kept in cents.
- Fixed point in embedded and flight systems.

# Chapter 08 — Characters and Text Encoding

### §08.01 Characters Are Numbers
Builds on: §05.02

- Character sets, and the history of ASCII (1963).
- Control characters.
- Character arithmetic (`'A' + 1`, `'7' - '0'`).

### §08.02 Escape Sequences and the Meaning of a Newline
Builds on: §08.01

- `\n`, `\t`, `\0`, `\\`, and hexadecimal and octal escapes.
- LF against CR LF.
- What the terminal actually does with these characters.

### §08.03 Beyond ASCII: Unicode and UTF-8
Builds on: §08.02

- Code pages, and the Unicode idea.
- The design of UTF-8 (Thompson and Pike, 1992).
- Multibyte characters; `u8""` literals and `char8_t` (C23).
- Why `strlen` counts bytes rather than letters.

### §08.04 Reading and Writing Characters
Builds on: §08.03

- `getchar` and `putchar`.
- `EOF`, and why `getchar` returns `int`.
- Reading until EOF (Ctrl+D), and line-buffered terminals.

### §08.05 Classifying Characters
Builds on: §08.04

- `<ctype.h>`.
- Why the argument must be an `unsigned char` value or `EOF`.
- Converting digit characters to their values.

# PART III — EXPRESSIONS: HOW C COMPUTES

# Chapter 09 — Expressions and Their Evaluation

### §09.01 What an Expression Is
Builds on: §06.02

- Value, type and side effect.
- Expression statements, and full expressions.

### §09.02 Precedence and Associativity Are Grammar
Builds on: §09.01

- Parse trees: how the compiler groups `a + b * c`.
- The precedence table derived from the grammar rather than memorized.

### §09.03 Order of Evaluation and Sequencing
Builds on: §09.02

- Grouping is not order.
- Unspecified order of evaluation (`f() + g()`).
- Sequence points (C99) and "sequenced-before" (C11).
- Why `i = i++ + ++i` is undefined behaviour.

### §09.04 lvalues and rvalues
Builds on: §09.03

- What can stand on the left of `=`, and what cannot.
- Modifiable lvalues.
- Why `5 = x` is an error.

### §09.05 Constant Expressions and Compile-Time Evaluation
Builds on: §09.04

- Integer constant expressions.
- Constant folding, seen in the `-S` output.
- The link with `constexpr` (§06.06).

# Chapter 10 — Arithmetic and Conversions

### §10.01 The Arithmetic Operators
Builds on: §09.05, §04.04

- `+`, `-`, `*`, `/` and `%`.
- Integer division truncates toward zero (fixed only in C99).
- The sign of `%`, and the identity `a == (a/b)*b + a%b`.
- Division by zero, and `INT_MIN / -1`.

### §10.02 How Hardware Multiplies and Divides
Builds on: §10.01

- The AVR has no divide instruction, so division calls a `libgcc` routine; what it costs.
- Shifts in place of powers of two, and the trap with signed values.

### §10.03 Integer Promotions
Builds on: §10.02, §05.03

- Why `char + char` becomes `int`, and the reasoning behind it.
- The effect on AVR code size.
- `uint8_t` surprises (for example, `~` applied to a `uint8_t`).

### §10.04 The Usual Arithmetic Conversions
Builds on: §10.03

- Conversion rank.
- The signed/unsigned trap: why `-1 < 0u` is false.
- Mixing integers and floating-point values.

### §10.05 Casts: Conversions on Purpose
Builds on: §10.04, §07.07

- What a cast does to values and to bits.
- Float-to-int truncation, and undefined behaviour when the value is out of range.
- Int-to-float rounding (2²⁴ + 1).
- When a cast hides a bug.

### §10.06 The Math Library
Builds on: §10.05, §03.06

- `<math.h>` and `-lm`.
- `pow`, `sqrt`, and `floor`/`ceil`/`round`/`trunc`.
- Error reporting; `<tgmath.h>`.
- Case study: compound interest computed in `double` and in integer cents.

# Chapter 11 — Assignment, Increment and Compound Operators

### §11.01 Assignment Is an Expression
Builds on: §10.04, §09.04

- The value of an assignment, and chained assignment.
- Conversion on assignment.
- The `=` / `==` trap, and how compilers warn about it.

### §11.02 Compound Assignment
Builds on: §11.01

- `+=` and its relatives.
- The left-hand operand is evaluated only once.
- How these operators map to machine instructions.

### §11.03 Increment and Decrement
Builds on: §11.02, §09.03

- Prefix against postfix semantics.
- The machine view.
- The `++i` against `i++` performance myth.
- Undefined combinations.

# Chapter 12 — Truth and Logic in Expressions

### §12.01 Truth in C
Builds on: §05.05, §10.04

- Zero and non-zero.
- Relational and equality operators yield `int` 0 or 1.
- Comparing floating-point values and pointers.

### §12.02 Logical Operators and Short-Circuit Evaluation
Builds on: §12.01

- `&&`, `||` and `!`.
- Short-circuit evaluation as hidden control flow, seen as branches in assembly.
- Guard expressions.
- De Morgan's laws.

### §12.03 The Conditional Operator
Builds on: §12.02

- `?:` as an expression, and the type of its result.
- Branchless machine code.

### §12.04 The Comma Operator
Builds on: §12.03

- Sequencing within an expression.
- Where the comma is an operator, and where it is only punctuation.

# Chapter 13 — Bits as a Tool: Bitwise Operators

### §13.01 AND, OR, XOR and NOT on Bits
Builds on: §12.02, §04.03

- Truth tables applied bit by bit.
- The contrast with the logical operators.
- The properties of XOR.

### §13.02 Shifts
Builds on: §13.01, §10.03

- Shifts as multiplication and division by powers of two.
- Shifting by the type's width or more.
- Right shift of a signed value (implementation-defined); left shift of a negative value.

### §13.03 Masks: Set, Clear, Toggle, Test
Builds on: §13.02

- Building masks with `(1u << n)`.
- Extracting and inserting multi-bit fields.

### §13.04 Bit Manipulation in Practice
Builds on: §13.03

- Flag bytes.
- `<stdbit.h>` (C23): counting bits, and leading or trailing zeros.
- Byte swapping.
- A preview of hardware registers.

### §13.05 Detecting Errors with Bits
Builds on: §13.04

- Parity, checksums, and the intuition behind CRCs.
- In orbit: why satellite links and stored memory are protected by error-detecting codes.

# PART IV — CONTROL: SHAPING THE FLOW

# Chapter 14 — The Flow of Control

### §14.01 Statements and Blocks
Builds on: §09.01

- The kinds of statement.
- Compound statements.
- The empty statement, and the stray-semicolon bug.

### §14.02 Control at the Machine Level
Builds on: §14.01, §01.05

- The program counter, and sequential execution.
- Conditional and unconditional branches.
- Compare-and-branch on the AVR and on x86-64.

### §14.03 From goto to Structured Programming
Builds on: §14.02

- Spaghetti code.
- Böhm–Jacopini (1966) and Dijkstra (1968).
- Sequence, selection and iteration; single entry and single exit.

### §14.04 Designing Algorithms
Builds on: §14.03

- Pseudocode, and flowcharts (with their limits).
- Top-down stepwise refinement.
- A worked design from problem statement to code.

# Chapter 15 — Selection

### §15.01 if and if…else
Builds on: §14.04, §12.02

- Nested `if` and `else if` chains.
- The dangling `else`, and how the grammar resolves it.
- Why to always use braces.

### §15.02 How Selection Compiles
Builds on: §15.01

- Branches in the generated code.
- Pipelines and branch prediction, explained intuitively.
- Branchless alternatives.

### §15.03 The switch Statement
Builds on: §15.02

- Why multi-way dispatch exists.
- `case` labels are labels within a statement.
- Constant case expressions; `default`.
- Fall-through, and C23's `[[fallthrough]]`.
- Duff's device, as proof that labels are only labels.

### §15.04 How switch Compiles
Builds on: §15.03

- Jump tables against chains of comparisons.
- Why case values must be constants.

### §15.05 State Machines
Builds on: §15.04

- States, events and transitions.
- Button debouncing on the AVR.
- A small protocol parser.
- In orbit: a satellite mode manager, including safe mode.

# Chapter 16 — Iteration

### §16.01 The Anatomy of a Loop: while
Builds on: §15.01

- Why repetition is needed.
- The condition, the body, and making progress.
- How `while` compiles to a backward branch.

### §16.02 Counter-Controlled Iteration
Builds on: §16.01

- The four parts of a control variable.
- Off-by-one errors.
- Half-open ranges `[0, n)`, and why C counts from zero (Dijkstra, 1982).

### §16.03 Floating-Point Control Variables
Builds on: §16.02, §07.06

- Your 0.05 experiment, reconstructed with the exact stored values.
- Why `<= 1.01` only seemed to work.
- Counting with an integer and deriving the fractional value from it.
- The general rule.

### §16.04 Sentinel-Controlled Iteration and Input Loops
Builds on: §16.03, §08.04

- Choosing a sentinel, and the priming read.
- EOF as a sentinel.
- Checking `scanf`'s return value.

### §16.05 The for Statement
Builds on: §16.04

- The grammar of the header: three optional expressions and two required semicolons, and why `for()` is an error.
- Equivalence with `while`, and the one difference involving `continue`.
- Declaring the control variable in the header, and its scope.
- The comma in a `for` header.

### §16.06 Infinite Loops and the Super Loop
Builds on: §16.05, §03.07

- `for(;;)` against `while(1)`.
- An infinite loop as a bug, and as a deliberate design.
- The embedded super loop; Arduino's `main()` reconstructed.
- What happens if `main` returns on the AVR.
- When a compiler may assume that a loop terminates (C11 onward).

### §16.07 The do…while Statement
Builds on: §16.06

- Executing the body first.
- Input validation.
- Compiled form, and a preview of the `do { } while (0)` macro idiom.

### §16.08 Nested Loops and Reasoning About Loops
Builds on: §16.07

- Common patterns.
- Growth of work (n²).
- Loop invariants, and arguments that a loop terminates.

### §16.09 Loops at the Machine Level
Builds on: §16.08

- What `-O2` does: strength reduction, unrolling and vectorization.
- Counting down to zero on the AVR.
- Reading the assembly.

# Chapter 17 — Altering the Flow: break, continue and goto

### §17.01 break and continue
Builds on: §16.09, §15.03

- Their meaning in loops and in `switch`.
- Behaviour in nested loops.
- Structured alternatives.

### §17.02 goto and Labels, Used Rightly
Builds on: §17.01

- The cleanup pattern (as used in the Linux kernel).
- Escaping from nested loops.
- The rules on jumps.
- The positions taken by MISRA and by the NASA coding rules.

# PART V — FUNCTIONS AND PROGRAM STRUCTURE

# Chapter 18 — Functions

### §18.01 Why Functions Exist
Builds on: §17.02

- Abstraction and decomposition.
- The subroutine's history (EDSAC).
- A function as a contract, and why the inside of a contract is still examined in this book.

### §18.02 Defining and Calling Functions
Builds on: §18.01

- Parameters against arguments.
- `return`, and `void` functions.
- The flow of call and return.

### §18.03 Pass by Value
Builds on: §18.02

- Arguments are copied.
- Conversions applied to arguments.
- Why a function cannot change its caller's variable (which motivates pointers).

### §18.04 Declarations and Prototypes
Builds on: §18.03, §02.05

- Why declarations exist.
- Old-style (K&R) declarations.
- Implicit `int` and implicit declaration: history, and why GCC now rejects them.
- `()` against `(void)` through C17, and in C23.

### §18.05 The Standard Library as Functions
Builds on: §18.04, §03.06

- Headers declare; libraries define.
- Reading the manual pages (`man 3`).
- A survey of the standard headers.

### §18.06 Pseudo-Random Numbers
Builds on: §18.05

- `rand` and `srand`.
- The mechanics of a linear congruential generator.
- Seeding, and modulo bias.
- A simulation case study.
- Hardware entropy on the ESP32.

### §18.07 Designing Good Functions
Builds on: §18.06

- Cohesion.
- Parameter design.
- Returning a status against returning a value.
- `inline` and `static inline`.

# Chapter 19 — The Call Stack

### §19.01 What the Stack Is
Builds on: §18.07, §01.04

- Last in, first out.
- The stack-pointer register, and push and pop.
- The direction of growth.

### §19.02 A Function Call on x86-64
Builds on: §19.01

- The System V ABI: argument registers, `call`/`ret`, frames.
- A walk-through in `gdb`.

### §19.03 A Function Call on the AVR
Builds on: §19.02

- avr-gcc's calling convention.
- `CALL` and `RET`.
- The 2 KB RAM budget.

### §19.04 Local Variables and Lifetime
Builds on: §19.03

- Automatic storage.
- Why returning the address of a local variable is wrong.
- Drawing stack frames.

### §19.05 Recursion
Builds on: §19.04

- Base case and recursive case.
- Factorial; Fibonacci's explosion of calls.
- The Towers of Hanoi.
- Recursion against iteration; tail calls.

### §19.06 Stack Overflow and Stack Budgets
Builds on: §19.05

- Linux: guard pages and `SIGSEGV`.
- The AVR: silent corruption.
- Measuring stack use with `-fstack-usage`.
- Why flight-software rules forbid recursion.

# Chapter 20 — Scope, Lifetime and Linkage

### §20.01 Scope
Builds on: §19.04

- Block, file, function and prototype scope.
- Shadowing.

### §20.02 Storage Duration
Builds on: §20.01

- Automatic, static, allocated and thread storage.
- Static local variables.
- Where each kind lives in memory.

### §20.03 Linkage
Builds on: §20.02

- External, internal and no linkage.
- `extern`, and `static` at file scope.
- Tentative definitions (and GCC 10's `-fno-common` default).
- One definition per program.

### §20.04 Designing Module Interfaces
Builds on: §20.03

- Information hiding with `static`.
- The public header.
- A preview of opaque types.

# Chapter 21 — Multi-File Programs and the Linker

### §21.01 Translation Units and Separate Compilation
Builds on: §20.04, §03.05

- Why programs are split into files.
- The cost of rebuilding, and what separate compilation saves.

### §21.02 Header Files Done Properly
Builds on: §21.01

- Declarations belong in headers; definitions do not.
- Include guards.
- Self-contained headers.
- Why each implementation file includes its own header.

### §21.03 Object Files and Symbols in Depth
Builds on: §21.02

- `nm` symbol types: `T`, `U`, `D`, `B`.
- Relocations.
- Experiments.

### §21.04 How the Linker Resolves Symbols
Builds on: §21.03

- The resolution algorithm.
- Duplicate and undefined symbols.
- Weak symbols.

### §21.05 Static Libraries
Builds on: §21.04

- `ar` archives, and the extraction rule.
- Link order, as in your experiment.
- Circular dependencies, and `--start-group`.

### §21.06 Shared Libraries
Builds on: §21.05

- `.so` files and position-independent code.
- The dynamic linker; `ldd`.
- `--as-needed`, and how it interacts with order.

### §21.07 The Framework Pattern: Who Owns main?
Builds on: §21.06, §16.06

- Arduino reconstructed on Fedora.
- Weak default hooks.
- A preview of callbacks.

### §21.08 Build Automation with make
Builds on: §21.07

- The dependency graph, and rules.
- Why build systems exist.
- The Arduino build process: sketch → `.cpp` → prototypes generated.

# Chapter 22 — The Preprocessor

### §22.01 What the Preprocessor Is and Why C Has One
Builds on: §21.08, §03.03

- Text processing before compilation.
- History.
- Its place among the phases of translation.

### §22.02 #include in Depth
Builds on: §22.01

- Search paths: `-I`, and `<>` against `""`.
- Seeing what is included with `-H`.

### §22.03 Object-Like Macros
Builds on: §22.02

- Named constants.
- Why `const`, `enum` and `constexpr` are often better.
- Macros have no scope.

### §22.04 Function-Like Macros
Builds on: §22.03

- Parenthesization.
- Double evaluation.
- `do { } while (0)`.
- `#` and `##`.
- `__VA_ARGS__` and `__VA_OPT__`.

### §22.05 Conditional Compilation
Builds on: §22.04

- `#if`, `#ifdef` and `#elifdef`.
- Detecting the platform (`__AVR__`).
- `__has_include`.
- `NDEBUG`.

### §22.06 Predefined Macros and Diagnostics
Builds on: §22.05

- `__FILE__`, `__LINE__` and `__func__`.
- `#error`, `#warning` and `#pragma`.

### §22.07 Advanced Preprocessor Techniques
Builds on: §22.06

- X-macros.
- How `<avr/io.h>` defines `PORTB`.
- `#embed` (C23).
- `typeof` and `_Generic` for type-generic code.

# PART VI — MEMORY IN DEPTH: ARRAYS, POINTERS, STRINGS

# Chapter 23 — Arrays

### §23.01 Why Arrays Exist
Builds on: §22.07, §06.03

- Contiguous storage.
- Index → address: base + i × size.

### §23.02 Defining and Initializing Arrays
Builds on: §23.01

- Initializer lists and designated initializers.
- Zero fill.
- `sizeof a / sizeof a[0]`.

### §23.03 Bounds and Buffer Overflows
Builds on: §23.02

- No bounds checking, and why.
- Out-of-bounds access is undefined behaviour.
- The Morris worm (1988).
- Detection with the address sanitizer.

### §23.04 Arrays and Functions
Builds on: §23.03

- An array decays to a pointer when passed.
- Passing the length.
- `const` array parameters, and `[static n]`.

### §23.05 Array Case Studies
Builds on: §23.04

- Histograms.
- Frequency counting.
- Lookup tables (a sine table in AVR flash).

### §23.06 Sorting
Builds on: §23.05, §19.05

- Bubble, selection and insertion sort, traced by hand.
- Stability.
- Merge sort.
- `qsort`.

### §23.07 Searching and the Growth of Work
Builds on: §23.06

- Linear against binary search.
- The intuition behind big-O notation.
- Measuring with `clock()`.

### §23.08 Multidimensional Arrays
Builds on: §23.07

- Row-major layout.
- The address formula.
- Matrices (linking to linear algebra).
- Image and frame buffers.

### §23.09 Variable-Length Arrays
Builds on: §23.08

- Their status in C99, C11 and C23.
- Stack danger.
- Why embedded code avoids them.

# Chapter 24 — Pointers

### §24.01 Why Pointers Exist
Builds on: §23.09, §18.03

- Indirection.
- Sharing data without copying it.
- Hardware addresses.
- History.

### §24.02 Pointer Basics
Builds on: §24.01

- Reading declarations.
- `&` and `*`.
- The null pointer: `NULL`, `0` and `nullptr` (C23).

### §24.03 Simulating Pass by Reference
Builds on: §24.02

- `swap`.
- `scanf`'s `&`, finally explained.
- Returning several results.

### §24.04 const and Pointers
Builds on: §24.03

- Pointer to `const` against a `const` pointer.
- The right-left rule for reading declarations.
- `const` as part of an API contract.

### §24.05 Pointer Arithmetic
Builds on: §24.04

- Scaling by the size of the type.
- One past the end.
- Subtraction, and `ptrdiff_t`.

### §24.06 Pointers and Arrays
Builds on: §24.05

- `a[i]` is `*(a+i)`.
- Why arrays are still not pointers (`sizeof`, `&a`).

### §24.07 Pointers to Pointers and Arrays of Pointers
Builds on: §24.06

- Ragged arrays.
- A preview of `argv`.

### §24.08 void Pointers and Generic Code
Builds on: §24.07

- `void *`.
- `memcpy`.
- `qsort` comparators.

### §24.09 Function Pointers
Builds on: §24.08

- Functions have addresses.
- Callbacks and dispatch tables.
- Interrupt vector tables; `attachInterrupt`.

### §24.10 When Pointers Go Wrong
Builds on: §24.09

- Dangling and wild pointers.
- Strict aliasing.
- `restrict`.

# Chapter 25 — Strings

### §25.01 What a C String Is
Builds on: §24.06, §08.03

- A null-terminated array of characters.
- Why C chose a terminator rather than a stored length (Pascal-style strings).
- The cost: `strlen` takes time proportional to the length.

### §25.02 String Literals
Builds on: §25.01

- Where they are stored, and why they are immutable.
- `char *s` against `char s[]`.
- On the AVR: string literals in RAM, against `PROGMEM`.

### §25.03 The String Library, Rebuilt by Hand
Builds on: §25.02

- Writing `strlen`, `strcpy`, `strcmp`, `strchr` and `strstr` ourselves.
- Comparing our versions with libc.

### §25.04 Handling Strings Safely
Builds on: §25.03

- Why `gets` was removed (C11).
- `strncpy`'s surprising behaviour.
- `snprintf`, and `strlcpy`.
- Why Annex K failed.

### §25.05 Converting Between Text and Numbers
Builds on: §25.04

- `strtol` and `strtod` with error checking.
- Writing `itoa`: how `printf` produces `%d`.

### §25.06 Tokenizing and Parsing
Builds on: §25.05

- How `strtok` works, and its hidden state.
- A serial-command parser.

### §25.07 Command-Line Arguments
Builds on: §25.06, §24.07

- `argc` and `argv`, and their layout in memory.
- The environment.

# Chapter 26 — Dynamic Memory

### §26.01 Why the Heap Exists
Builds on: §25.07, §20.02

- Lifetimes that are not known when the program is compiled.

### §26.02 malloc, calloc, realloc and free
Builds on: §26.01

- What each function does.
- Checking for failure.
- The pitfalls of `realloc`.

### §26.03 How an Allocator Works
Builds on: §26.02

- Free lists.
- Splitting and coalescing blocks.
- Writing a tiny allocator.

### §26.04 Memory Errors and the Tools That Find Them
Builds on: §26.03

- Leaks, use-after-free and double free.
- Valgrind and the address sanitizer.

### §26.05 Dynamic Memory in Microcontrollers and Spacecraft
Builds on: §26.04

- Fragmentation over long running times.
- Heap and stack colliding on the AVR.
- Memory pools.
- The NASA and MISRA rules on dynamic memory.

# Chapter 27 — The Memory Map of a Program

### §27.01 Sections and Segments
Builds on: §26.05, §03.05

- `.text`, `.data`, `.bss`, the heap and the stack.
- The `size` command.
- Where each kind of variable lands.

### §27.02 Virtual Memory on Linux
Builds on: §27.01

- Private address spaces, and pages.
- `/proc/self/maps`.
- What a segmentation fault really is.

### §27.03 The ATmega328P Memory Map
Builds on: §27.02

- Flash, SRAM and EEPROM.
- `PROGMEM` and `pgm_read_byte`.

### §27.04 Linker Scripts and Map Files
Builds on: §27.03

- How the linker places sections in memory.
- Reading a `.map` file.

# PART VII — STRUCTURED DATA

# Chapter 28 — Structures

### §28.01 Why Structures Exist
Builds on: §27.04

- Records: grouping different kinds of data under one name.

### §28.02 Defining and Using Structures
Builds on: §28.01

- Designated initializers.
- Assignment copies the whole structure.
- Passing and returning structures, and what it costs.

### §28.03 Layout: Padding and Alignment
Builds on: §28.02, §06.04

- `offsetof`.
- Ordering members to save space.
- Packed structures, and their cost.

### §28.04 Pointers to Structures
Builds on: §28.03

- The `->` operator.
- Self-referential structures.
- Opaque handles (`FILE`).

### §28.05 typedef
Builds on: §28.04

- What `typedef` really creates.
- Naming conventions.

### §28.06 Structures for Protocols and Telemetry
Builds on: §28.05

- Telemetry packet layout.
- Serializing data properly rather than copying it with `memcpy`.
- In orbit: an example modelled on CCSDS (space data) packets.

# Chapter 29 — Unions, Bit-Fields and Enumerations

### §29.01 Unions
Builds on: §28.06

- Shared storage.
- Tagged unions.
- Type punning.

### §29.02 Bit-Fields
Builds on: §29.01, §13.03

- Implementation-defined layout.
- Why bit-fields are a poor portable map of hardware registers.

### §29.03 Enumerations
Builds on: §29.02

- The underlying type, and C23's fixed underlying types.
- `-Wswitch`.

# Chapter 30 — Building Data Structures

### §30.01 Linked Lists
Builds on: §29.03, §26.02

- Insertion and deletion.
- The pointer-to-pointer technique.

### §30.02 Stacks and Queues
Builds on: §30.01

- Implementations with arrays and with lists.

### §30.03 Ring Buffers
Builds on: §30.02

- Masking with a power-of-two size.
- A single producer and a single consumer.
- A UART receive buffer.

### §30.04 Binary Trees
Builds on: §30.03

- Binary search trees.
- Traversals.
- Recursion, again.

### §30.05 Hash Tables
Builds on: §30.04

- Hash functions.
- Collisions, and chaining.

### §30.06 Choosing a Data Structure
Builds on: §30.05

- Time against memory.
- Static pools for embedded systems.

# PART VIII — C AND THE OUTSIDE WORLD

# Chapter 31 — Streams and Formatted I/O

### §31.01 The Stream Abstraction
Builds on: §30.06, §08.04

- `FILE`, and file descriptors beneath it.
- Buffering modes, and `fflush`.

### §31.02 printf in Depth
Builds on: §31.01

- The grammar of a conversion specification.
- Rounding in the displayed value (your 0.95).
- Format-string vulnerabilities.

### §31.03 How Variadic Functions Work
Builds on: §31.02

- `<stdarg.h>`.
- Default argument promotions.
- Why a mismatched format is undefined behaviour.

### §31.04 scanf in Depth
Builds on: §31.03

- The matching rules.
- Return values.
- `fgets` + `strtol` as the safer path.

### §31.05 Redirection and Pipes
Builds on: §31.04

- `<`, `>`, `|` and `2>`.
- Exit statuses in shell scripts.

### §31.06 printf on a Microcontroller
Builds on: §31.05

- Output through the UART.
- avr-libc stdio, and retargeting.
- The cost in flash.

# Chapter 32 — Files

### §32.01 Files and the Operating System
Builds on: §31.06

- Paths.
- Permissions on Linux.

### §32.02 Opening, Reading, Writing and Closing
Builds on: §32.01

- The modes of `fopen`.
- Text against binary.
- Character, line and formatted I/O.

### §32.03 Binary Files and Random Access
Builds on: §32.02

- `fread` and `fwrite`; `fseek` and `ftell`.
- Record files.

### §32.04 Handling File Errors
Builds on: §32.03

- `errno`, `perror` and `strerror`.
- The `while (!feof(f))` bug.

### §32.05 Beneath stdio: System Calls
Builds on: §32.04

- `open`, `read` and `write`.
- Watching a program's system calls with `strace`.

# Chapter 33 — Termination, Signals and Time

### §33.01 Ending a Program
Builds on: §32.05

- `return` from `main`, `exit`, `_Exit` and `abort`.
- `atexit`.

### §33.02 Signals
Builds on: §33.01

- What Ctrl+C really does.
- `SIGSEGV`.
- What is safe inside a signal handler: `volatile sig_atomic_t`.

### §33.03 Time and Measurement
Builds on: §33.02

- `time`, `clock` and `timespec`.
- Benchmarking honestly.

# PART IX — CORRECTNESS, SAFETY AND RELIABILITY

# Chapter 34 — Writing Correct C

### §34.01 A Catalogue of Undefined Behaviour
Builds on: §33.03, §02.04

- Code that works at `-O0` and fails at `-O2`.

### §34.02 Assertions and Contracts
Builds on: §34.01

- `assert` and `static_assert`.
- Preconditions and postconditions.

### §34.03 Error-Handling Strategies
Builds on: §34.02

- Status codes, out-parameters and cleanup paths.

### §34.04 Tools That Find Bugs
Builds on: §34.03

- Sanitizers, Valgrind, `-fanalyzer` and `cppcheck`.
- A method for debugging with `gdb`.

### §34.05 Testing C Code
Builds on: §34.04

- Writing a test harness.
- Testing embedded code on the host.

### §34.06 Secure C
Builds on: §34.05

- The CERT C rules.
- Validating input.
- Overflow in size calculations.

# Chapter 35 — C for Systems That Must Not Fail

### §35.01 What Goes Wrong in Space
Builds on: §34.06, §01.04

- Radiation and single-event upsets; latch-up.
- Lessons from real mission failures (verified case studies).

### §35.02 Coding Standards for Critical Software
Builds on: §35.01

- NASA/JPL's "Power of Ten" rules and MISRA C, with the reason behind each rule.

### §35.03 Defensive Techniques in Software
Builds on: §35.02

- Watchdogs.
- Memory scrubbing and EDAC (error detection and correction).
- Triple modular redundancy in software.
- Safe modes.

### §35.04 Determinism and Resource Bounds
Builds on: §35.03

- Bounded loops.
- Worst-case execution time.
- Static stack analysis.

# PART X — C ON THE METAL, AND BEYOND

# Chapter 36 — Bare-Metal C on the ATmega328P

### §36.01 Leaving Arduino Behind
Builds on: §35.04, §21.08

- `avr-gcc`, `-mmcu`, and `avrdude`.
- Blinking an LED with no framework.

### §36.02 Reading a Datasheet
Builds on: §36.01

- Navigating the ATmega328P datasheet.
- The register summary.

### §36.03 Memory-Mapped I/O
Builds on: §36.02, §24.02

- `DDRB`, `PORTB` and `PINB`.
- Pull-up resistors.
- What happens electrically at the pin.

### §36.04 volatile
Builds on: §36.03

- What the optimizer does to a register access without `volatile`, proven in the assembly.
- What `volatile` does not promise.

### §36.05 Startup Code and the Vector Table
Builds on: §36.04, §27.04

- Writing a minimal startup.
- What Arduino's `init()` adds.

### §36.06 Arduino's Functions, Reconstructed
Builds on: §36.05

- Inside `digitalWrite`.
- Why it is slow.
- Writing a fast equivalent.

# Chapter 37 — Interrupts, Timers and Peripherals

### §37.01 Polling Against Interrupts
Builds on: §36.06

- The hardware interrupt sequence.
- `ISR()` and `reti`.

### §37.02 Timers
Builds on: §37.01

- Prescalers, overflow and compare match.
- How `millis()` and `delay()` really work.

### §37.03 Sharing Data with an Interrupt
Builds on: §37.02

- Atomicity on an 8-bit CPU.
- `ATOMIC_BLOCK`.

### §37.04 The UART at Register Level
Builds on: §37.03, §30.03

- Baud-rate mathematics.
- An interrupt-driven receive buffer.

### §37.05 ADC and PWM
Builds on: §37.04

- Sampling a voltage.
- Generating analog-like output.

### §37.06 Sleep Modes and Power
Builds on: §37.05

- Power budgets (on battery and on a satellite).
- Waking up.

# Chapter 38 — Concurrency and the C Memory Model

### §38.01 Threads and Data Races
Builds on: §37.06

- Multiple cores.
- `<threads.h>` and pthreads.

### §38.02 Atomics and Memory Ordering
Builds on: §38.01

- `_Atomic`.
- Reordering by compilers and CPUs.
- Happens-before.

### §38.03 Tasks on the ESP32 with FreeRTOS
Builds on: §38.02

- Tasks, queues and mutexes.
- `app_main`: another framework that owns `main`.

# Chapter 39 — Toward the Machine Designer

### §39.01 Reading Compiler Output Fluently
Builds on: §38.03

- Mapping C constructs onto AVR, x86-64 and Xtensa code.

### §39.02 Optimization and the As-If Rule
Builds on: §39.01

- Inlining and link-time optimization (LTO).
- `-Os` for embedded targets.
- Measuring the results.

### §39.03 Inline Assembly
Builds on: §39.02

- `asm volatile`.
- When it is truly necessary.

### §39.04 C and C++ at the Boundary
Builds on: §39.03

- Sketches are C++.
- Name mangling, and `extern "C"`.

### §39.05 How a C Compiler Works
Builds on: §39.04

- Lexer, parser, AST, IR and code generation.
- Building a tiny expression compiler (a bridge to designing languages).

### §39.06 C on a Processor You Design
Builds on: §39.05

- What an ISA must provide for C.
- Designing an ABI.
- Porting a compiler (a bridge to processor design).

# Chapter 40 — Reference Appendices

### §40.01 Operator Precedence and Associativity Table
### §40.02 ASCII Table and Escape Sequences
### §40.03 Number-System Conversion Tables
### §40.04 C Standard Versions: Feature Map (C89 → C23)
### §40.05 ATmega328P Register Quick Reference
### §40.06 Fedora Toolchain Command Reference

# Summary

- 41 chapters (00–40) in 10 parts: 39 teaching chapters, one preliminary chapter and one reference chapter.
- 228 sections, each one topic followed to its roots. Every "Builds on" reference points backward; none points forward.
- Order of dependence: the machine → C's purpose and toolchain → data → expressions → control → functions and program structure → memory → structured data → the outside world → reliability → the metal.
