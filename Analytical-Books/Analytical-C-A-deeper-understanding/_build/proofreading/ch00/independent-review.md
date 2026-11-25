# Independent review: §00.01 and §00.02

Reviewer's toolchain: gcc-14 (Ubuntu 14.2.0-4ubuntu2~24.04.1), avr-gcc 7.3.0 + avr-libc 2.0.0+Atmel3.7.0, file-5.45, x86-64 Ubuntu 24.04, POSIX locale unless stated. Sources were checked on the web on 24 Nov 2026.

Severity key: **error** = definitely wrong, shown by evidence. **likely error** = probably wrong, or not supported by any source. **improvement** = imprecise, misleading or inconsistent wording, or a layout defect that does not change meaning.

---

## §00.01 How This Book Teaches

1. **"We return to this case in Chapter 07, where you will have the tools to work through the arithmetic yourself."** (History box)
   - Category: cross-ref. Severity: likely error.
   - Problem: No Chapter 07 entry in toc.json mentions the Patriot case or the arithmetic of a 24-bit chopped 1/10. The nearest bullets are §07.08 ("Fixed point in embedded and flight systems") and §07.06 ("the accumulation of error"). A search of the whole TOC for "Patriot", "Dhahran" or "tenth" finds nothing, and §35.01 ("Lessons from real mission failures") is about space.
   - Fix: Name the section (most naturally §07.08, because the Patriot arithmetic was fixed-point) and add a matching bullet to the TOC. Otherwise, drop the promise.

2. **TOC bullet for 00.01: "How claims are labelled: established fact, standard text, implementation behaviour, and the author's inference."**
   - Category: cross-ref/coverage. Severity: error.
   - Problem: The section defines only *three* kinds of statement (Table 00.01-2: standard, implementation, inference). The fourth kind, *established fact*, is missing, even though the section uses it: the Patriot history box is neither standard, implementation nor inference, and Sources says the advice is "the author's judgement, not established fact".
   - Fix: Add a fourth row, "Established fact (documented history, datasheet values, published sources)", and say how it is marked (a source is cited). Otherwise, change the TOC bullet.

3. **Terms introduced: "`double`: … on the machines in this book, a 64-bit binary floating-point number."**
   - Category: fact. Severity: error.
   - Problem: This is false for the Arduino Uno, one of the book's three machines. `avr-gcc -mmcu=atmega328p -dM -E -x c /dev/null` gives `__SIZEOF_DOUBLE__ 4` and `__DBL_MANT_DIG__ 24`. The approved TOC says so too, at §07.07: "`double` on avr-gcc (32-bit by default …)".
   - Fix: "on the laptop and the ESP32, a 64-bit IEEE 754 binary number; on the AVR with avr-gcc's default settings, only 32 bits (§07.07)."

4. **Precisely speaking box: "an implementation announces that it follows Annex F by defining the macro `__STDC_IEC_559__`."**
   - Category: fact. Severity: improvement.
   - Problem: C23 introduced `__STDC_IEC_60559_BFP__`, which supersedes `__STDC_IEC_559__`; cppreference's C23 page says "This macro supersedes `__STDC_IEC_559__`" (https://www.cppreference.com/w/c/23.html). In my reading of the C23 drafts, the old macro is marked obsolescent, but I have not checked the final text. The book targets C23, and its own rule (line 128) is that a Precisely speaking box names the version whenever versions differ. This box does not. On the verification machine, glibc's `stdc-predef.h` defines both macros: `gcc-14 -std=c23 -dM -E` gives `__STDC_IEC_559__ 1` and `__STDC_IEC_60559_BFP__ 201404L`.
   - Fix: "(in C23, `__STDC_IEC_60559_BFP__`; the older `__STDC_IEC_559__` is kept for compatibility)". It is also more precise to say that glibc's `stdc-predef.h` defines the macro, based on GCC's `__GCC_IEC_559`.

5. **"The equality operator `==` compares the stored values exactly"** (also Table 00.01-2, "`==` compares stored values exactly.", and Self-check 4(b))
   - Category: fact/precision. Severity: improvement.
   - Problem: As a statement about the *standard*, this is imprecise. `==` compares the operands' *values after the usual arithmetic conversions*. Where `FLT_EVAL_METHOD` is not 0, operands and floating constants (such as `0.3`) may be evaluated in a wider range and precision than the stored type. NaN compares unequal to itself even though the same bits are stored, and +0 == −0 although their stored bits differ. On x86-64, `__FLT_EVAL_METHOD__` is 0 (confirmed with `-dM -E`), so the example's result is unaffected.
   - Fix: "compares the values of its operands exactly, with no tolerance (special cases such as NaN and the evaluation format in §07.05 and §07.07)." Both topics are in the TOC.

6. **"Nothing is broken here. The processor performed its arithmetic exactly according to its rules, on the values it was given."** (also "Line 5 adds the two values")
   - Category: fact/mechanism. Severity: error.
   - Problem: In Listing 00.01-1, `0.1 + 0.2` is a constant expression, and GCC folds it at compile time even at `-O0`. `gcc-14 -std=c23 -O0 -S sum_check.c` contains no `addsd`. Instead it holds the ready-made constant `.long 858993460 / .long 1070805811` = 0x3FD3333333333334 = 0.30000000000000004, loaded with `movsd .LC0(%rip)`. The processor only compares (`ucomisd`). For a book that promises "what the compiler produced, what the processor executed", this misstates the mechanism.
   - Fix: "The compiler computed the sum while translating the program, using the same IEEE 754 rules the processor would use (round to nearest). The processor then only compared the two stored values. (Chapter 03 shows how to see this with `gcc -S`.)"

7. **Experiment 00.01-3: "Add the line `printf("%.55f\n", 0.1);` … What does the fact that the digits *stop* tell you about the stored value?"**
   - Category: program/consistency. Severity: error.
   - Problem 1: With `%.55f`, printf prints exactly 55 digits *because the precision says 55*. The reader cannot observe that the digits stop. My run printed `0.1000000000000000055511151231257827021181583404541015625`, which is exactly 55 digits, the same as the precision. Only a larger precision shows the expansion ending: `%.70f` prints the same digits followed by fifteen `0`s.
   - Problem 2: Printing *exact* digits beyond 17 significant digits is glibc behaviour. The C standard only recommends correct rounding up to `DECIMAL_DIG` significant digits. Other C libraries have printed zeros or garbage after about 17 digits. The answer presents the result as universal, against the section's own "implementation" rule.
   - Fix: Use `%.70f` (and say "the digits after the 55th are all zero"). Add "(this exact expansion is what the GNU C library prints; the standard does not require it)".

8. **The question: "Why should 0.95 + 0.05 fail to equal 1.00, when every schoolchild knows it does?"**
   - Category: consistency/precision. Severity: improvement.
   - Problem: The premise is false as written. `0.95 + 0.05 == 1.00` evaluates to 1 in both `double` and `float` (tested). The loop stops because the *accumulated* value is not 0.95. After 19 additions of 0.05 it is 0.95000000000000028866 (double) or 0.95000016689300537109 (float). The 21st value is 1.00000000000000022204 (double) or 1.00000011920928955078 (float), which fails `<= 1.00`. The student's naive question can stay, but a strict book should not leave a false premise unmarked.
   - Fix: "Why should adding 0.05 twenty times fail to reach 1.00 …?" Alternatively, keep the line and mark it as the student's assumption, to be corrected in §16.03.

9. **Connection: "… a clock that adds a tenth of a second at every tick. The last of these has a sobering history."**
   - Category: fact/consistency. Severity: improvement.
   - Problem: The Patriot clock did not add 0.1 at every tick. It counted *integer* tenths and multiplied the count by a 24-bit *fixed-point* (chopped) 1/10. The history box itself says this correctly, so the two passages disagree, and the box never says the arithmetic was fixed-point rather than `double`. Source: the UMN "Patriot Missile Failure" page ("24 bit fixed point register"), https://www-users.cse.umn.edu/~arnold/disasters/patriot.html. Skeel, *SIAM News* vol. 25 no. 4, July 1992, p. 11, reproduced at https://mate.uprh.edu/~pnegron/notas4061/patriot.htm.
   - Fix: "a clock that counts tenths of a second and converts the count to seconds". In the box: "converted it to seconds by multiplying by 1/10 held in a 24-bit fixed-point register".

10. **"You may have noticed that the walk around the cycle used three different kinds of sentence."** and Table 00.01-2, column "Example from this section", Inference row: "Most surprises of this kind … come from equality tests …"
    - Category: consistency. Severity: improvement.
    - Problem: The walk contains no inference sentence. The inference example appears nowhere in the section except in this table and in Sources. It also carries none of the markers the section announces ("the author's view is…", "this suggests…", *Inference*).
    - Fix: Add a labelled sentence to the walk, for example after "Nothing is broken here": "*Inference:* most surprises of this kind …".

11. **"Every output shown in the book comes from an actual run, and the toolchain and machine are named beside it, as in Table 00.01-1."**
    - Category: consistency. Severity: improvement.
    - Problem: The Output block after Listing 00.01-1 does not name the toolchain beside it. It is named only in Table 00.01-1's caption and in Sources. The same holds in §00.02 for the broken.c and warnings.c outputs, which are "the author's output" with the toolchain only in Sources.
    - Fix: Add a caption line to each output block (for example "Output (GCC 14.2, x86-64 Ubuntu 24.04)"), or reword the claim to "named in the caption or in Sources and verification".

12. **"No section depends on a later one."**
    - Category: consistency. Severity: improvement.
    - Problem: §00.01 itself depends on §00.02 for its experiments ("If you have not yet set one up, read §00.02 first") and for line 70 ("You will learn how to compile and run a program in §00.02"). The TOC "builds" lines contain no forward dependency (I checked every section), so the claim holds for the TOC but not for §00.01's experiments.
    - Fix: "Apart from the experiments of this first section, which need the workbench of §00.02, no section depends on a later one."

13. **Figure 00.01-1 asset mismatch** (`![Figure 00.01-1 …](fig1.png)`)
    - Category: layout/consistency. Severity: error.
    - Problem: The supplied `s0001_fig1.png` (1712×1400) shows the five steps in a *circle*. The figure embedded in the PDF (page 2, 1945×256, per `pdfimages -list`) is a different image, a *single row* of five boxes with a curved dashed arrow. One of the two is stale. The .md also references `fig1.png`/`fig2.png`, while the delivered files are named `s0001_fig1.png`/`s0001_fig2.png`. The §00.02 figure has the same naming difference.
    - Fix: Decide which design is approved, regenerate, and make the source reference and the file name agree.

14. **Figure 00.01-1 readability in the PDF** (page 2)
    - Category: layout. Severity: improvement.
    - Problem: The row-format image is scaled to the full text width at 256 px high. The box text prints at about 5 pt, and the label "a new question" at about 4 pt, which is hard to read on paper. This is also the label the text points to ("This is the dashed arrow in Figure 00.01-1").
    - Fix: Use the circular layout or a two-row layout, at a height that gives text of at least 8 pt.

15. **Page breaks in the PDF**
    - Category: layout. Severity: improvement.
    - Problem: Page 4 is about 40% empty below "5. Connection" because the History box was pushed to page 5. Page 6 is about 45% empty before Figure 00.01-2. Three tables split with only one row carried over: Table 00.01-3 (pages 7→8), Table 00.01-4 (pages 8→9) and Table 00.01-5 (pages 9→10).
    - Fix: Allow boxes to split, or float the figure, and keep short tables together.

16. **Sources, PDF page 13: "option -" / "std=c23 -Wall …"**
    - Category: layout. Severity: improvement.
    - Problem: Inline code breaks at the leading hyphen, so it reads like a hyphenated word. §00.02's PDF has the same fault on page 14: "Without -" / "std=c23".
    - Fix: Use a non-breaking hyphen (U+2011) or no-break spans for inline options.

17. **Sources: "All programs … compiled with GCC 14.2.0 (`gcc-14`, option `-std=c23 …`) … Your Fedora system's GCC 15 or 16 should produce identical output, since the format of `double` is the same."**
    - Category: program/consistency/language. Severity: improvement.
    - Problem (a): "option" should be "options".
    - Problem (b): The printed digits also depend on the C library's printf (glibc), not only on the format of `double`. Fedora also uses glibc, so the conclusion probably holds.
    - Problem (c): This is an unlabelled inference. Under the book's own convention it should be marked as such, or confirmed on the reader's GCC 16.
    - Evidence: My gcc-14 runs reproduce all three outputs exactly (Listing 00.01-1: `0.30` / `0.30000000000000004` / `0`; Experiment 2: `0.75` / `0.75000000000000000` / `1`).

18. **Notation table: "C99, C11, C17, C23 — Editions of the C standard, named after the year of their completion"**
    - Category: fact. Severity: improvement.
    - Problem: This is defensible, but it will confuse a careful reader. C17 is ISO/IEC 9899:2018 and C23 is ISO/IEC 9899:2024, so the publication years differ from the names. `__STDC_VERSION__` (201710L, 202311L) follows the completion date.
    - Fix: Add "(C17 was published in 2018 and C23 in 2024; §02.05)".

19. **History box: "The official investigation by the US General Accounting Office (report GAO/IMTEC-92-26, 1992) …"**
    - Category: fact. Severity: improvement.
    - Problem: GAO describes the report as a review made "at a congressional request" (https://www.gao.gov/products/imtec-92-26). It is not *the* official investigation; the Army had its own. The report was published on 4 February 1992. The other facts check out: 25 Feb 1991, Dhahran, 28 soldiers killed, about 100 h, about 0.34 s, a range-gate shift of several hundred metres (GAO gives 687 m).
    - Fix: "A review by the US General Accounting Office …". In Sources, add "SIAM News 25(4), July 1992, p. 11" for Skeel.

20. **Table 00.01-3: ESP32 "Xtensa, 32-bit"**
    - Category: fact. Severity: improvement.
    - Problem: This is true for the original ESP32 (dual-core Xtensa LX6). However, many current "ESP32" boards are ESP32-C3, C6 or similar parts, which use a RISC-V core. A reader buying a board could get the wrong one.
    - Fix: Name the exact chip or module the book uses (for example "ESP32 (ESP32-WROOM-32), Xtensa LX6").

21. **Figure 00.01-1, box 4: "Precise rule — what C guarantees"**
    - Category: consistency. Severity: improvement.
    - Problem: The text says step 4 states "what is guaranteed, *and by whom*". The step-4 box in this very walk includes implementation facts (GCC and glibc define the macro), and Table 00.01-4 defines the box as "what the standard says … or what a named implementation does".
    - Fix: "what is guaranteed, and by whom".

22. **Language**
    - Category: language. Severity: improvement.
    - "The best teaching books of C" should be "teaching books on C".
    - Experiment 00.01-2: "using only the idea of halves, quarters and eighths". Eighths are not needed for 0.5 + 0.25, so this is harmless but inexact.
    - The PDF prints straight ASCII double quotes in the body ("may be approximate"), while the figure uses curly quotes (“Why does this happen?”). Pick one style.

---

## §00.02 Setting Up the Workbench on Fedora

23. **The PDF of §00.02 is a stale render and does not match 00.02.md**
    - Category: layout/consistency. Severity: error.
    - Evidence: Comparing `pdftotext` output with the .md shows these differences:
      - (a) PDF p.3: "Make a folder … separate from the book itself", with the path `~/Documents/C-Programming/Analytical-C-Lab/00-02`. The .md (lines 61–65) uses `…/Analytical-Books/Analytical-C-A-deeper-understanding/_Analytical-C-Lab/00-02`.
      - (b) PDF p.4 lacks the .md sentence "Beneath it, Table 00.02-2 also records what a current Fedora system printed."
      - (c) PDF Table 00.02-2 has 3 rows ("GCC 15 or 16 … (Fedora 43 and later) | From GCC's documentation; run it and confirm"). The .md has 4 rows, including the GCC 16.2.1 row.
      - (d) PDF Listing 00.02-3 line 6 has the comment "// make pin PB5 (Arduino pin 13) an output", which also wraps out of the gutter. The .md has "// pin PB5 (Arduino pin 13): output".
      - (e) The PDF answer to Experiment 00.02-1 and the "Toolchain used for outputs" bullet are older wordings.
    - Fix: Re-render from the current .md before publication. My other layout remarks on §00.02 refer to this stale PDF.

24. **"…the book does not need it until Chapter 38."** and "Chapter 38 will check them again …" (ESP32 toolchain)
    - Category: cross-ref. Severity: error.
    - Problem: The approved TOC needs the ESP32 much earlier:
      - §05.03 "16-bit `int` on the AVR; 32-bit on the ESP32" and "Experiment: printing the sizes on all three machines"
      - §07.07 "The ESP32's single-precision FPU, and the cost of software floating point"
      - §18.06 "Hardware entropy on the ESP32"
      - §02.06 "The meaning of `main` … under ESP-IDF/FreeRTOS"
    - It also contradicts §00.01 ("every important idea is tested on **three machines**").
    - Fix: "until §05.03" (or "until Chapter 05"), and say where the install will be checked again.

25. **Table 00.02-3: "Without it, GCC names the program `a.out`, for historical reasons (Chapter 03)."**
    - Category: cross-ref. Severity: likely error.
    - Problem: No Chapter 03 bullet in toc.json mentions `a.out` or its history (03.01–03.08 checked; a TOC search for "a.out" returns nothing).
    - Fix: Add the topic to a §03.05 or §03.07 bullet, or remove the signpost.

26. **"Type it exactly; you will understand every line by the end of Chapter 03."** (Listing 00.02-1)
    - Category: cross-ref. Severity: error.
    - Problem: According to the TOC, several elements of the listing come later:
      - `sizeof`: §06.02
      - `size_t` and `%zu`: §05.04, §06.02, §31.02 ("The grammar of a conversion specification")
      - `%ld`: §31.02
      - predefined macros in general (`__VERSION__`): §22.06
    - Only `__STDC_VERSION__` (§02.05) and `__STDC_HOSTED__` (§02.06) are covered before Chapter 03.
    - Fix: "…most of it by the end of Chapter 03; `sizeof` and the `%zu` and `%ld` conversions are explained in §06.02 and §31.02."

27. **"The names that begin and end with two underscores are predefined macros … The program simply prints four of them."**
    - Category: consistency/fact. Severity: error.
    - Problem: Only three macros are printed (`__STDC_VERSION__`, `__VERSION__`, `__STDC_HOSTED__`). Line 8 prints `sizeof(int)`, and `sizeof` is an operator, not a macro. It is also worth saying that `__VERSION__` is GCC-specific, while the other two are standard. That is exactly the standard/implementation distinction taught in §00.01.
    - Fix: "prints three of them, and the size of an `int`".

28. **"A **warning** means your text is valid C, a program *is* produced …"** and Terms: "Warning: a message saying the text is valid C but probably not what you meant"
    - Category: fact. Severity: error.
    - Problem: GCC issues mere warnings, and still produces a program, for code that is *not* valid ISO C. These are exactly the diagnostics that `-pedantic`, recommended in this section, exists for. Evidence: `gcc-14 -std=c23 -Wall -Wextra -pedantic inv.c` on
      ```c
      int a[0];
      int main(void){ char *s="x"; unsigned char *u=s; return (int)(a[0]+*u); }
      ```
      gives `warning: ISO C forbids zero-size array 'a' [-Wpedantic]` and `warning: pointer targets in initialization … differ in signedness [-Wpointer-sign]`. Both are constraint violations, yet the exit status is 0 and `inv` is produced.
    - Fix: "A warning means a program is still produced, but the compiler has noticed something suspicious: sometimes legal code that is probably a mistake, sometimes a breach of the standard that GCC tolerates." Adjust the Terms entry to match.

29. **Table 00.02-3, `-pedantic`: "Warn about any use of extensions that strict ISO C does not allow. Together with `-std=c23`, it makes GCC hold you to the standard."**
    - Category: fact. Severity: error.
    - Problem: The GCC manual (Warning Options, -Wpedantic) says it will "diagnose all programs that use forbidden extensions, and some other programs that do not follow ISO C". It also says "-Wpedantic does not cause warning messages for use of the alternate keywords whose names begin and end with '__'" and that "Pedantic warnings are also disabled in the expression that follows `__extension__`" (https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html). It is not "any use", and it does not guarantee conformance.
    - Fix: "Issue the warnings that strict ISO C requires and diagnose forbidden GNU extensions. It catches many, but not all, departures from the standard."

30. **Table 00.02-3, `-std=c23`: "Follow the C23 standard exactly as published."**
    - Category: fact. Severity: improvement.
    - Problem: The GCC manual says that with a base standard "the compiler accepts all programs following that standard plus those using GNU extensions that do not contradict it" (https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html). GCC 14's C23 support is also incomplete, and the section's own box says "most of C23".
    - Fix: "Use the C23 language, turning off GNU extensions that conflict with it (non-conflicting extensions remain; `-pedantic` warns about them)."

31. **Error position: the journey and the Self-check 7 answer contradict each other**
    - Category: consistency. Severity: error.
    - Journey: "Notice that it reports the problem at the point where it *noticed* the mistake, which is the end of line 5. With a missing semicolon those are the same place."
    - Answer: "The compiler cannot know a semicolon is missing until it reads the next token, the `}` … It reports the position where the statement should have ended, the end of line 5."
    - Problem: The answer is right. The compiler *notices* the problem at the `}` on line 6, but *reports* it at the end of line 5, where the mistake was made. The journey says the opposite, and its "those are the same place" does not name which two places it means.
    - Fix: "The compiler noticed the mistake only when it reached the `}` on line 6, but GCC reports it where the missing token belonged, the end of line 5. Later you will meet errors that are reported some distance from where they were made …"

32. **`file blink.elf` output block: "blink.elf: ELF 32-bit LSB executable, Atmel AVR 8-bit, version 1 (SYSV), statically linked"**
    - Category: program. Severity: error.
    - Problem: The actual output (file-5.45, same avr-gcc 7.3.0 build) is `blink.elf: ELF 32-bit LSB executable, Atmel AVR 8-bit, version 1 (SYSV), statically linked, with debug_info, not stripped`. The book's output is truncated, and output blocks must be exact. The avr-size block matches exactly, tabs included (text 162, hex a2).
    - Fix: Copy the full line. Also note that Fedora's newer `file` may word it differently.

33. **broken.c and warnings.c output blocks: locale and version**
    - Category: program. Severity: improvement.
    - Problem: These outputs match gcc-14 in the POSIX locale. On Fedora, whose default locale is UTF-8, GCC prints typographic quotes. With `LC_ALL=C.UTF-8`, `od -c` shows `342 200 230 main 342 200 231`, so the reader will see ‘main’ and not 'main'. GCC also emits 21 trailing spaces after `| ~` in broken.c, which the block omits; this is invisible, but the block is not byte-exact. The text does not flag that these diagnostics come from GCC 14 and may differ in layout under GCC 16, against §00.01's own promise.
    - Fix: Add a note saying "(on Fedora you will see curly quotes ‘ ’; the diagnostic layout may differ slightly in GCC 16)", or run the examples with `LC_ALL=C`.

34. **Under the hood (-v) box: `as -v --64 -o /tmp/ccju82AT.o /tmp/ccxJcr07.s`**
    - Category: program. Severity: improvement.
    - Problem: With the book's standard command, which includes `-g`, gcc-14 prints ` as -v --gdwarf-5 --64 -o /tmp/….o /tmp/….s`. The box's line omits `--gdwarf-5` without marking an omission, yet Sources says "the omitted parts are marked `...`". It matches only when `-g` is not used. Experiment 00.02-3 asks the reader to use their normal command plus `-v`, so they will see `--gdwarf-5`.
    - Fix: Insert `...`, or state the exact command used.

35. **VS Code step 3: `$ dnf check-update && sudo dnf install code`**, with Sources: "commands reproduced as given there"
    - Category: fact/program. Severity: error.
    - Problem (a): `dnf check-update` exits with status **100** when updates are available. The DNF5 documentation says "DNF5 will exit with code 100 if updates are available" (https://dnf5.readthedocs.io/en/stable/commands/check-upgrade.8.html). On a typical machine with pending updates, `&&` therefore skips the install silently.
    - Problem (b): Microsoft's page (https://code.visualstudio.com/docs/setup/linux) currently gives `sudo dnf install --refresh code` for Fedora. `dnf check-update` appears there only in a troubleshooting entry, so "reproduced as given there" is not true.
    - Fix: `$ sudo dnf install --refresh code`, and update the explanation of "the third command".

36. **Precisely speaking box (DNF): "`dnf search <word>` lists the packages whose names or descriptions contain that word."**
    - Category: fact. Severity: error.
    - Problem: DNF5 searches the Name and Summary fields by default. Description and URL are searched only with `--all` (https://dnf5.readthedocs.io/en/latest/commands/search.8.html). A secondary point: Table 00.01-4 defines a *Precisely speaking* box as about the C standard or a named C implementation, and a package-manager note does not fit that definition.
    - Fix: "names or summaries (add `--all` to search descriptions too)". Move the note to plain text or another box.

37. **Sources: "avr-gcc 15.2 on Fedora 43 and later."**
    - Category: fact. Severity: likely error.
    - Problem: packages.fedoraproject.org/pkgs/avr-gcc/avr-gcc/ shows 15.3.0-1 for Fedora 43, 44, 45 and Rawhide, as of the date the section says it was checked. The gcc row is correct (15.3.1 on F43, 16.2.1 on F44; F45 also has 16.2.1).
    - Fix: Change to 15.3. Also note that Fedora's avr-libc is 2.2.1 (2.2.1-5 on F44), against the author's 2.0.0, which is a further reason the blink size may differ.

38. **"The third line says that the program is running in a hosted environment … Chapter 02 explains the alternative, a freestanding environment, which is exactly what a bare microcontroller is."**
    - Category: fact. Severity: likely error (misleading).
    - Problem: `__STDC_HOSTED__` is a compile-time statement about the *implementation*. It does not detect where the program is running. avr-gcc 7.3 for the ATmega328P defines `__STDC_HOSTED__ 1` by default (`avr-gcc -mmcu=atmega328p -dM -E -x c /dev/null`), so a reader who infers that "the Uno would report 0" would be wrong.
    - Fix: "The third line says that the *compiler* claims to be a hosted implementation … (avr-gcc claims this too unless given `-ffreestanding`; §02.06 explains why)."

39. **On the metal box: "You now have *two* AVR compilers: Fedora's … and the one bundled inside the Arduino IDE …"** and "When this book writes bare-metal C, it uses Fedora's compiler"
    - Category: consistency. Severity: error.
    - Problem 1: Nothing in this section installs the Arduino IDE, so the reader may have only one AVR compiler.
    - Problem 2: Every AVR output in the section (the 162 bytes, the `file` line, 201112) comes from avr-gcc 7.3, not from "Fedora's compiler".
    - Fix: "If you also have the Arduino IDE installed, you have two …". Mark the AVR outputs as avr-gcc 7.3 results to be confirmed with Fedora's avr-gcc 15.3, as the agreed verification policy requires.

40. **Table 00.02-2 row: "avr-gcc 7.3 with no option … | Prints 201112 | Run by the author on the same base version"**
    - Category: consistency. Severity: improvement.
    - Problem: Listing 00.02-1 cannot print anything on an Uno; the section itself says a bare microcontroller has no `printf` output. The value is correct: `avr-gcc -dM -E` gives `__STDC_VERSION__ 201112L`. However, it was obtained some other way, not by running the listing.
    - Fix: Say how it was obtained (for example "value of the macro, read with `avr-gcc -mmcu=atmega328p -dM -E`").

41. **"Every compile command in this book uses the same options unless the text says otherwise."** compared with the avr-gcc command `-Os -Wall -Wextra`
    - Category: consistency. Severity: improvement.
    - Problem: The AVR command drops `-std=c23 -pedantic -g` without saying why. avr-gcc 7.3 rejects the option: `avr-gcc: error: unrecognized command line option '-std=c2x'`. Fedora's avr-gcc 15 accepts it.
    - Fix: Explain the omission, or use `-std=c23 -pedantic` with Fedora's compiler.

42. **"Run these commands once everything is installed. Each should print a version number rather than 'command not found'."**
    - Category: consistency. Severity: improvement.
    - Problem: `man 3 printf`, `avrdude -?` and `groups` do not print version numbers; the table itself says so.
    - Fix: "Each should work rather than print 'command not found'."

43. **"…notice only that it contains no `printf`, because a bare microcontroller has no screen."**
    - Category: fact. Severity: improvement.
    - Problem: The laptop's `printf` does not need a screen either; it writes to a stream. avr-libc provides `printf`, and §31.06 is "printf on a Microcontroller". The real reason is that no output stream is connected by default.
    - Fix: "…because on a bare microcontroller nothing is connected to standard output until you connect it (§31.06)."

44. **Experiment 00.02-5 answer: "They share a name and a formatting style, but they are different programs."**
    - Category: fact/language. Severity: improvement.
    - Problem: printf(3) is a library *function*, not a program. Also, typing `printf` in bash runs the bash *builtin* (documented by `help printf`), not the coreutils program described in `man 1 printf`; that man page itself warns that the shell may have its own version.
    - Fix: "…but one is a program (and a shell builtin) and the other a function inside the C library."

45. **dialout: "Group membership is read when you log in, so the change takes effect only after logging out and in again."** and "it usually appears as the device file `/dev/ttyACM0`"
    - Category: fact. Severity: improvement (I could not verify this on Fedora).
    - Problem: On systemd/GNOME desktops, the user's service manager can outlive a logout, so a reboot is sometimes needed. Many Uno clones with a CH340 USB chip appear as `/dev/ttyUSB0`, not `ttyACM0`.
    - Fix: "log out and in again (or restart if `groups` still lacks it)". Mention `ttyUSB0` for clones.

46. **ESP-IDF repository: `gpgcheck=0`**
    - Category: consistency. Severity: improvement.
    - Problem: The commands match Espressif's v6.1.1 page exactly (https://docs.espressif.com/projects/esp-idf/en/v6.1.1/get-started/linux-setup.html). However, the section earlier stresses that dnf "checks their signatures" and that packages carry "a digital signature proving where it came from". This repository turns signature checking off, and the text does not say so.
    - Fix: Add one sentence: "Note `gpgcheck=0`: this repository's packages are not signature-checked; you are trusting the HTTPS download alone."

47. **Terminal-block notation for heredoc and wrapped lines** (ESP-IDF block lines 274–279; VS Code `echo -e` line)
    - Category: consistency. Severity: improvement.
    - Problem: The heredoc body lines (`[eim]` … `EOF`) have neither `$ ` nor `# `. §00.01's notation table says only "Type the part after the `$`", so a reader may not type those lines.
    - Fix: Extend the notation ("lines without `$` inside a command continue it and must be typed"), or render them with a `> ` continuation prompt.

48. **Over-long lines in terminal and output blocks**
    - Category: layout. Severity: error.
    - Problem: These .md lines exceed 78 characters:
      - line 64: 113 chars
      - line 65: 107 chars
      - line 200: 260 chars
      - line 239: 84 chars
      - line 249 (output): 90 chars
    - In the PDF, the avr-gcc command wraps `blink.elf` onto a new line with no continuation mark, the `file` output wraps "statically / linked", and the VS Code `echo -e` string wraps across four lines in the middle of the string. A reader typing from the page can split these commands incorrectly.
    - Fix: Use `\` line continuations, a shell variable for the long lab path (for example `LAB=~/Documents/…/_Analytical-C-Lab`), and a heredoc for the repo file, as the ESP-IDF block already does. All C listings are within 78 characters in the .md.

49. **Other layout in the (stale) PDF**
    - Category: layout. Severity: improvement.
    - Listing 00.02-3 line 6 wraps out of the gutter (p.8; already fixed in the .md, needs a re-render).
    - Table 00.02-4 splits across pp.10/11.
    - The Experiment 00.02-1 answer breaks inline code as "Without -" / "std=c23" (p.14); see #16.

50. **TOC coverage for 00.02**
    - Category: cross-ref/coverage. Severity: improvement.
    - Bullet 4 promises "the ESP32 toolchain (ESP-IDF), installed lightly on an 8 GB machine". The section deliberately does *not* install it, and "8 GB" is discussed only for VS Code. Align the TOC or the text.
    - Table 00.02-1 gives "§03.05" for `size`, but `size` belongs to §27.01 ("The `size` command"); §03.05 covers only `nm`, `objdump` and `readelf`.
    - Three more jobs are listed (avr-gcc, avr-libc, avrdude), but four packages are installed (plus avr-binutils).
    - The checklist (Table 00.02-4) omits `strace`, `nm`/`readelf`, `avr-size` and `code`.

51. **Precisely speaking box: "GCC 14 implemented most of C23 before the standard's final number was fixed, and reports the provisional value `202000L`."**
    - Category: fact. Severity: likely error (unverified).
    - Problem: The value `202000L` itself is confirmed: gcc-14 `-std=c23` prints 202000, and with no option it prints 201710. However, as far as I can determine, `202311L` was already in the committee's final drafts (N3219/N3220, early 2024) before GCC 14.1 was released in May 2024. GCC kept 202000L because ISO publication, and its own support, were incomplete, not because the number was unknown.
    - Fix: "GCC 14, released before C23 was formally published and with incomplete support, still reports the provisional value `202000L`." Check against the GCC 15 changes or the GCC commit that changed the value.

52. **Language and small wording points**
    - Category: language. Severity: improvement.
    - Self-check 6 answer: "'only warnings' means 'several suspected mistakes'" should be "one or more suspected mistakes".
    - Self-check 3 answer: "kept up to date automatically". dnf does not update automatically on a default Fedora install; it updates when you (or GNOME Software) run it. The journey's "kept up to date by the system" is safer.
    - "`sudo` ('do as the superuser')": the usual gloss is "superuser do" (or "substitute user, do").
    - "Adding it takes three commands": the third step contains two commands.
    - "Ctrl+` (the key above Tab)": this holds on US/UK layouts only; on many other layouts the key is elsewhere. Say "the backtick key".

53. **Heads-up, not an error in §00.02: TOC §03.02 says "The `gcc` *driver* and the separate programs it runs (`cpp`, `cc1`, `as`, `ld`), seen with `-v`"**
    - Category: cross-ref. Severity: improvement.
    - Problem: Modern GCC integrates the preprocessor into `cc1`, so `-v` shows no separate `cpp`. §00.02's Under the hood box shows this correctly (cc1, as, collect2). The TOC bullet should be corrected before §03.02 is written.

---

## What I checked and found correct

- **Line references:**
  - Listing 00.01-1: lines 5 to 8, and Experiment 00.01-2's "line 5" and "line 8".
  - Listing 00.02-2: `5:22`, "the `}` on line 6".
  - Listing 00.02-4: `4:23`, `9:9`.
  - All C listing lines are 78 characters or fewer.
- **Outputs (exact, with gcc-14 -std=c23 -Wall -Wextra -pedantic):**
  - Listing 00.01-1
  - Experiment 00.01-1 and 00.01-2 answers
  - The digits in Experiment 00.01-3
  - Table 00.01-1, all four values (checked with Python `Decimal`)
  - Listing 00.02-1 (`202000`, `14.2.0`, `1`, `4 bytes`); with no `-std`, gcc-14 gives 201710 as the answer says
  - broken.c (exit 1; text matches apart from the quote and trailing-space notes in #33)
  - Experiment 00.02-2 (0, then 1, then 2 warnings, in the order and with the columns shown)
  - The avr-size block, byte-exact
  - `./blink.elf`: "cannot execute binary file: Exec format error"
  - The cc1, as, collect2 order with `-v`
- **The opening loop:** both float and double versions stop at 0.95, and 20 values are printed.
- **AVR:**
  - blink.c builds without warnings, also with `-std=c11 -pedantic`.
  - `DDB5`/`PORTB5` exist, PB5 = Arduino pin 13.
  - The delay loop is 0x1869FF iterations at 16 MHz, as expected for 500 ms.
  - avr-gcc 7.3 defaults: `__STDC_VERSION__` 201112L and `sizeof(int)` 2.
- **Predefined macros:**
  - `__STDC_IEC_559__` is defined on x86-64 glibc.
  - `__STDC_VERSION__` values 199901/201112/201710/202311.
  - GCC 15 defaults to gnu23 (GCC manual: "GNU dialect of ISO C23. This is the default for C code").
  - GCC 8–14 defaulted to gnu17.
- **Fedora:**
  - DNF5 is the default from Fedora 41.
  - These packages exist: gcc, gdb, make, binutils, valgrind, man-pages, strace, avr-gcc, avr-libc, avr-binutils (2.45), avrdude (8.0 on F43/F44).
  - gcc is 15.3.1 on F43 and 16.2.1-3 on F44, consistent with the reader's "16.2.1 20261029 (Red Hat 16.2.1-3)".
  - The dialout group owns tty devices.
- **VS Code:** steps 1 and 2 match Microsoft's page.
- **ESP-IDF:** the repo file, `eim-cli` and `eim install` match Espressif's v6.1.1 page.
- **Patriot facts:** date, place, 28 killed, GAO report number and February 1992, about 100 h, about 0.34 s, several hundred metres, and Skeel's point about the conversion being improved only in some places.
- **Numbering:** listings, figures and tables are sequential in both sections.
- **Answers:** every self-check has an answer and every answer addresses its question; the exceptions are noted in #7 and #31.
- **"You have now met four" boxes** is correct at that point in the text.
- **Cross-references that match the TOC:**
  - §00.01: §16.03, §07.08 (money in cents), §04.01, §02.05.
  - §00.02: §03.05, §19.02, §26.04, §21.08, §18.05; Chapter 32 for strace (§32.05); Chapter 02 for freestanding (§02.06); Chapter 05 for 16-bit int (§05.03); Chapter 36 for blink and upload (§36.01, §36.03); Chapter 03 for the -v steps and their order (§03.02).
  - The Figure 00.01-2 chapter labels (01, 03, 06, 14, 19, 21, 22, 27, 36, 37, 39) match the TOC.
  - "Builds on" lines match toc.json (00.01 "—", 00.02 "§00.01"), and toc.json has no forward "builds" dependencies.
- **Spelling:** British -ise/-our spelling is consistent within both sections. The TOC uses -ize ("Optimization", "Initializing", "Tokenizing"), which is a cross-document inconsistency to settle in the house style.

## Not verified

- GCC 15/16 diagnostic layout for broken.c and warnings.c, and GCC 16 output of Listing 00.01-1.
- The blink size with Fedora's avr-gcc 15.3 / avr-libc 2.2.1, and the wording of `file` on Fedora.
- Whether log-out/log-in is enough for dialout on Fedora 44 GNOME.
- The exact C23 wording on `__STDC_IEC_559__` obsolescence (only cppreference's "supersedes" was checked) and the history of GCC 14's 202000L (#51).
- The Arduino "Fix port access on Linux" article.
- The ESP-IDF disk size (already labelled an estimate).
- The reader's GCC 16.2.1 run (taken as reported).
- I did not run simavr: the 1.6 command-line tool has no VCD output option, so I checked the blink timing by disassembly instead.
