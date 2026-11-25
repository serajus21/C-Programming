# Forward commitments made in written sections

Each line: where the promise is made -> where it must be kept -> what must be delivered.
Checked at every chapter proofreading; a section that keeps a promise ticks it.

## Made in Chapter 00
- §00.01 -> §16.03: the 0.05 loop from the opening, with exact stored values.
- §00.01 -> §07.08: the Patriot (Dhahran, 1991) 24-bit fixed-point timing error, worked through arithmetically.
- §00.01 -> §04.01: binary and hexadecimal notation (0b1010, 0x2F) explained fully.
- §00.01 -> §02.05: the editions C99, C11, C17, C23 and how they are named.
- §00.02 -> Chapter 03 (§03.06 or §03.07): why the default output name is a.out (historical reasons).
- §00.02 -> Chapter 03: the order cc1 -> as -> collect2/ld, and why it must be this order.
- §00.02 -> §02.06: hosted vs freestanding environments.
- §00.02 -> Chapter 05 (§05.03): why int is 2 bytes on the Uno.
- §00.02 -> Chapter 36: every line of the C blink program; leaving the Arduino IDE behind.
- §00.02 -> Chapter 38: re-check the ESP-IDF installation steps against Espressif's documentation before use.
- §00.02 -> §32.05: first real use of strace.

## Made in Chapter 01
- §01.01 -> §36.03: how the Schmitt trigger at each digital input works (hysteresis), "what happens electrically at the pin".
- §01.01 -> §13.02 and §31.02: the shifts of the xorshift generator, and printf field widths (%7ld, %.4f, %%).
- §01.01 -> §04.02, §04.04: unsigned wraparound and signed overflow from a finite number of bits.
- §01.01 -> §35.01, §35.03: radiation upsets and the software defenses against them.
- §01.01 -> Chapter 07: why the pattern stored for 0.1 is not 0.1 (the root of §00.01's surprise).
- TOC note for §01.04 proofreading: its bullets should mention DRAM, which the section covers. KEPT (index v1.5).
- §01.02 -> §12.02: short-circuit evaluation with side effects; De Morgan's laws in C conditions.
- §01.02 -> §13.01: the bitwise operators &, |, ^ and ~ as gates applied to every bit.
- §01.02 -> §09.01: side effects, linked back to combinational logic as "pure functions".
- §01.02 -> §02.03, §39.02: what the as-if rule lets a compiler do with functions that have no side effects (TOC bullet added to §39.02).
- §01.02 -> §35.01: single-event latch-up, and current-sensing power cycling.
- §01.02 -> §36.03: the pin circuitry the ATmega328P datasheet actually draws.
- §01.03 -> §04.01, §04.02, §04.03: binary notation; unsigned arithmetic defined modulo 2^n; two's complement.
- §01.03 -> §04.05, §10.05: the Ariane 5 lesson (an out-of-range conversion to a 16-bit integer).
- §01.03 -> §13.01, §13.02: bitwise operators and shifts, as used in adder8.c.
- §01.03 -> §20.01: file-scope variables (the flags in adder8.c).
- §01.03 -> Chapter 03, §39.01: producing and reading assembly listings.
- §01.03 -> §39.03: inline assembly (asm volatile), as used in flags.ino.
- §01.04 -> §27.03: the ATmega328P data-memory map (registers, I/O, SRAM at 0x0100–0x08FF).
- §01.04 -> §27.02: why a laptop pointer is translated before it reaches the memory chips.
- §01.04 -> Chapter 24: a pointer as an address placed on the address wires.
- §01.04 -> §37.03: interrupts arriving at moments the program does not choose (software counterpart of metastability).
- §01.04 -> §38.01/§38.02: why one x86 instruction (addb) is not one indivisible action when two cores share a variable.
- §01.04 -> §13.05, §35.03: error detection; EDAC and memory scrubbing (with write-back).
- §01.04 -> §01.05: the program counter (14 bits on the ATmega328P, word-addressed flash). KEPT (§01.05).
- §01.05 -> §04.01: hexadecimal notation (0x39 = 0011 1001).
- §01.05 -> §29.03: enum (tiny.c).
- §01.05 -> §13.02, §13.03: >> and masking with & 0x1F, as field extraction.
- §01.05 -> Chapter 24: pointers, %p, converting a function address to a byte pointer; registers through which pointers reach memory (AVR X, Y, Z; x86-64 base + index).
- §01.05 -> §23.03, §34.06: code injection by buffer overflow, and writing C that avoids it.
- §01.05 -> §27.02: pages, per-page permissions, what a segmentation fault really is.
- §01.05 -> §03.07, §36.05, §16.06: reset vector -> start-up code -> main; Arduino's main calling setup().
- §01.05 -> §14.02, §15.02, §16.09, §16.06: if/while/for as tests and conditional jumps; for (;;) as a backward jump.
- §01.05 -> §02.03, §39.02: the as-if rule; why a + b became a constant.
- §01.05 -> §36.04: volatile (Hands-on A).
- §01.05 -> §03.05, §21.03: relocation.
- §01.05 -> §08.01: character codes (13 = carriage return).
- §01.05 -> §39.01: x86-64 variable-length decoding; Xtensa register windows.
- §01.05 -> Chapter 36 (§36.01): avrdude and uploading.
- §01.05 -> §01.06: the bits of 86 0F (KEPT, §01.06); programs written in one machine's instructions tied to it (KEPT, §01.06).
- §01.06 -> §06.03: byte order (endianness), little-endian storage.
- §01.06 -> §21.06: position-independent code.
- §01.06 -> §03.05, §03.06, §21.03: object files, relocations, the linker filling them in.
- §01.06 -> §36.03: DDRB/PINB, and toggling a pin by writing 1 to PIN.
- §01.06 -> §36.05: start-up code and the vector table that -nostartfiles leaves out.
- §01.06 -> §10.02: how hardware multiplies.
- §01.06 -> §19.03: avr-gcc's calling convention and register rules.
- §01.06 -> §39.03: instructions only assembly can reach; inline assembly.
- §01.06 -> Chapter 35: how modern flight software is written, with sources.
- §01.06 -> Chapter 02: the origins of C.
- §01.06 -> Chapter 10: why a + b on uint8_t is computed as int; conversion warnings.
- §01.06 -> Chapters 23, 25, 31: arrays, strings, strcmp, sscanf.
- §01.06 -> §02.03, §39.02: what the optimizer is permitted to do (-O0 vs -O2).
