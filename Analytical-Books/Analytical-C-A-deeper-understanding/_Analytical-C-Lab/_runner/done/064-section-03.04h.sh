F="$PWD/../_build/sections/03.04/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "for L in O0 O1 O2 O3 Os Og; do gcc $O -\$L -c ops.c -o z_\$L.o; echo \"-- \$L\"; size -A z_\$L.o | grep -E '^\\.(text|rodata|eh_frame|note)'; done"
run "for L in O0 O1 O2 O3 Os Og; do gcc $O -\$L -c ops.c -o y_\$L.o && gcc $O test_ops.c y_\$L.o -o ytest_\$L && echo \"\$L \$(./ytest_\$L)\"; done"
run "printf 'movl \$0x4004b0,%%edi\nmovq \$0x4004b0,%%rdi\nmovabsq \$0x4004b0,%%rdi\nmovb \$0,%%sil\n' | as -o enc.o - && objdump -d enc.o | tail -4"
run "avr-objdump -r avr_ops.o | head -12"
run "grep -o -w -m1 avx512f /proc/cpuinfo"
mkdir -p d3 && cp ops.c d3/
run "cd d3 && gcc -std=c23 -O2 -fdump-rtl-all -S ops.c && grep -l 'const_int 35' ops.c.*r.* | head -1"
run "gcc -O2 -Q --help=target | grep unroll; cd d3 && grep -i 'unrolled' ops.c.*r.loop2_unroll; sed -n '/Function sum_to/,/^}/p' ops.c.*t.optimized | head -40"
run "cat /usr/lib/rpm/redhat/redhat-hardened-cc1"
run "readelf -n hello_pie | grep -i -A1 'x86 feature'"
run "avr-gcc -mmcu=atmega328p -std=c11 -O2 avr_ops.c -o avr_ops2.elf && avr-objdump -d avr_ops2.elf | grep -E 'call|<main>'"
run "gcc -std=c23 -fPIE -pie hello.c -o hello_pie2 && objdump -d hello_pie2 | sed -n '/<main>:/,/ret/p'"
run "avr-gcc -mmcu=atmega328p -std=c11 -Wall -Wextra -pedantic -Os -S avr_hello.c -o avr_hello.s && grep -c '' avr_hello.s"
run "gcc $O -Os -S -fno-asynchronous-unwind-tables hello.c -o - | sed -n '/^main:/,/ret/p'"
cat > one_int.c <<'EOF'
#include <stdio.h>
int main(void) {
    int n = 7;
    printf("%d\n", n);
    return 0;
}
EOF
run "gcc $O -S -fno-asynchronous-unwind-tables one_int.c -o - | grep -E 'eax|call'"
cat > shift34.c <<'EOF'
#include <stdio.h>
#include <stdint.h>
int main(void) {
    volatile uint32_t ten = 10;
    uint64_t wrong = 0; uint32_t first = 0; int seen = 0;
    uint32_t x = 0;
    do {
        if ((uint32_t)(((uint64_t)x * 1717986919u) >> 34) != x / ten) {
            if (!seen) { first = x; seen = 1; }
            ++wrong;
        }
    } while (++x != 0);
    printf("shift 34: %llu mismatches, first at %u\n", (unsigned long long)wrong, (unsigned)first);
    return 0;
}
EOF
run "gcc $O -O2 shift34.c -o shift34 && ./shift34"
run "gcc $O -fsanitize=undefined -O0 -c ops.c -o ub.o && printf '#include <stdio.h>\nint sum_to(int);\nint main(void){ printf(\"%%d\\\\n\", sum_to(70000)); return 0; }\n' > ub_main.c && gcc $O -fsanitize=undefined ub_main.c ub.o -o ub && ./ub"
run "gcc $O -S -fverbose-asm call.c -o - | sed -n '/^main:/,/ret/p'"
