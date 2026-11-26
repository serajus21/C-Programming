S="$PWD/../_build/sections/03.04"; F="$S/fedora"; mkdir -p "$F"; cd "$F" || exit 1
cp ../*.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "gcc $O -S hello.c -o hello.s && wc -l hello.s && cat hello.s"
run "gcc $O -S -fno-asynchronous-unwind-tables hello.c -o hello_nocfi.s && wc -l hello_nocfi.s"
run "gcc $O hello.c -o hello && objdump -d hello | sed -n '/<main>:/,/ret/p'"
run "gcc $O -c hello.c -o hello.o && objdump -dr hello.o | sed -n '/<main>:/,\$p'"
run "gcc $O -S -masm=intel hello.c -o - | sed -n '/^main:/,/\\.cfi_endproc/p'"
run "gcc $O -S -fverbose-asm hello.c -o - | sed -n '/^main:/,/\\.cfi_endproc/p'"
run "gcc -v 2>&1 | tr ' ' '\\n' | grep -E 'pie|cf-protection|default' ; echo | gcc -dM -E - | grep -E '__pie__|__PIE__|__CET__|__SSP'"
run "gcc $O -fPIE -fcf-protection=full -S hello.c -o - | sed -n '/^main:/,/\\.cfi_endproc/p'"
run "gcc $O -fPIE -pie -fcf-protection=full hello.c -o hello_pie && objdump -d hello_pie | sed -n '/<main>:/,/ret/p' && file hello_pie"
run "gcc $O -S -fno-asynchronous-unwind-tables call.c -o - | sed -n '/^main:/,/ret/p'"
run "gcc $O call.c -o call && ./call"
run "gcc $O -O2 -S -fno-asynchronous-unwind-tables call.c -o - | sed -n '/^main:/,/ret/p'; gcc $O -O2 -S call.c -o - | grep -A3 '^\\.LC'"
for lv in O0 O1 O2 O3 Os Og; do run "gcc $O -$lv -S -fno-asynchronous-unwind-tables hello.c -o - | sed -n '/^main:/,/ret/p'"; done
for lv in O0 O1 O2 O3 Os Og; do run "gcc $O -$lv -S -fno-asynchronous-unwind-tables ops.c -o - | grep -v -E '^\\s*\\.(file|ident|section|text|p2align|globl|type|size|align|long|string)|^[0-4]:'"; done
for lv in O0 O1 O2 O3 Os Og; do run "gcc $O -$lv -c ops.c -o ops_$lv.o && size ops_$lv.o | tail -1"; done
for lv in O0 O1 O2 O3 Os Og; do run "gcc -$lv -Q --help=optimizers | grep -c '\\[enabled\\]'"; done
run "gcc -Q --help=optimizers | grep -c '\\[disabled\\]'"
for lv in O0 O2 Os; do run "gcc $O -$lv -c ops.c -o t_$lv.o && gcc $O test_ops.c t_$lv.o -o test_$lv && ./test_$lv"; done
run "clang -std=c23 -O2 -S -fno-asynchronous-unwind-tables ops.c -o - | sed -n '/^sum_to:/,/ret/p'"
run "clang $O -O2 -c ops.c -o t_clang.o && gcc $O test_ops.c t_clang.o -o test_clang && ./test_clang"
run "gcc $O -O2 check10.c -o check10 && time ./check10"
mkdir -p dumps && cd dumps && cp ../hello.c ../ops.c .
run "gcc -std=c23 -O0 -fdump-tree-all -fdump-rtl-all -S hello.c && ls hello.c.* | wc -l && ls hello.c.* | tr '\\n' ' '"
run "cat hello.c.*t.gimple"
run "grep -l '__builtin_puts' hello.c.*t.* | head -3; cat hello.c.*t.lower"
run "gcc -std=c23 -O2 -fdump-tree-all -fdump-rtl-all -S hello.c -o hello2.s && ls hello.c.* | wc -l"
run "gcc -std=c23 -O2 -fdump-tree-gimple -fdump-tree-ssa -fdump-tree-optimized -fdump-rtl-expand -S ops.c && cat ops.c.*t.gimple"
run "sed -n '/Function sum_to/,/^}/p' ops.c.*t.ssa"
run "sed -n '/Function div10/,/^}/p' ops.c.*t.optimized"
run "grep -c '' ops.c.*r.expand; sed -n '/Function div10/,/^;; Function/p' ops.c.*r.expand | grep -n -E 'mult|lshiftrt|udiv|const_int' | head -12"
cd ..
A="avr-gcc -mmcu=atmega328p -std=c11 -Wall -Wextra -pedantic"
for lv in O0 Os O2; do run "$A -$lv -S ops.c -o - | grep -v -E '^\\s*\\.(file|ident|section|text|globl|type|size)'"; done
for lv in O0 Os O2; do run "$A -$lv -c ops.c -o avrops_$lv.o && avr-size avrops_$lv.o | tail -1"; done
run "$A -Os -S avr_hello.c -o - | sed -n '/^main:/,/\\.size/p'"
run "$A -Os avr_ops.c -o avr_ops.elf && avr-objdump -d avr_ops.elf | sed -n '/<main>:/,/<__udivmodhi4_ep>/p'; avr-objdump -d avr_ops.elf | sed -n '/<__udivmodhi4_ep>:/,/ret/p'"
run "$A -Os -c avr_ops.c -o avr_ops.o && avr-nm avr_ops.o"
run "avr-gcc -mmcu=atmega328p -print-libgcc-file-name; avr-nm \$(avr-gcc -mmcu=atmega328p -print-libgcc-file-name) 2>/dev/null | grep -E ' T __udivmodhi4\$'"
