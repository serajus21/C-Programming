F="$PWD/../_build/sections/03.05/fedora"; mkdir -p "$F/y"; cd "$F/y" || exit 1
cp ../*.c ../../../03.04/avr_ops.c ../../../03.03/avr_blink.c . 2>/dev/null; cp ../hello.o . 
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "rpm -qf /usr/bin/file /usr/bin/xxd /usr/bin/nm /usr/bin/readelf"
LG=$(avr-gcc -mmcu=atmega328p -print-libgcc-file-name)
run "avr-nm -A $LG | grep -E ' T __do_copy_data| T __do_clear_bss'"
run "avr-objdump -h $LG 2>/dev/null | grep -B2 -A1 'init4' | head -8"
run "avr-ld --verbose -m avr5 | grep -n -E '__data_(start|end|load_start)'"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -S avr_hello.c -o - | tail -3"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -c avr_hello.c -o avr_hello.o && avr-objdump -dr avr_hello.o | sed -n '/<.L3>:/,\$p'"
run "cp hello.o s.o && strip s.o && readelf -S -W s.o | grep '\\]'"
run "readelf -d /bin/ls | grep FLAGS_1; readelf -h /lib64/libc.so.6 | grep OS/ABI; readelf -h /bin/ls | grep OS/ABI"
run "objcopy --strip-symbol=hello.c hello.o nofile.o && ld nofile.o -o x"
run "printf '.text\\ncall puts\\n' | as --32 -o t32.o && objdump -dr t32.o | tail -3"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -c avr_ops.c -o avr_ops.o && avr-objdump -dr avr_ops.o | grep -B1 -A1 -E 'call'"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -S avr_blink.c -o - | grep -n -w -E 'L0|1:|L0:' ; avr-gcc -mmcu=atmega328p -std=c11 -Os -c avr_blink.c -o avr_blink.o && avr-objdump -dr avr_blink.o | grep -n -B2 -A2 'L0'"
cat > constw.c <<'EOF'
#include <stdio.h>
const int primes[4] = {2, 3, 5, 7};
int main(void) {
    int *p = (int *)&primes[2];   // casting away const: undefined behavior
    *p = 9;
    printf("%d\n", primes[2]);
    return 0;
}
EOF
run "gcc $O constw.c -o constw && ./constw"
run "readelf -p .comment /usr/lib64/crt1.o /usr/lib64/crti.o /usr/lib/gcc/x86_64-redhat-linux/16/crtbegin.o /usr/lib64/crtn.o 2>&1 | grep -E 'File|GCC'"
run "gcc -std=c23 hello.o -o hello -v 2>&1 | grep collect2 | tr ' ' '\\n' | grep -n -E 'crt|hello.o|-lc\$|-lgcc'"
run "xxd -s 0x2a8 -l 64 hello.o"
run "readelf -x .shstrtab hello.o | head -3"
run "man nm 2>/dev/null | col -b | grep -n -E '^ +\"?[AaBbCDdRrTtUWw]\"?\\b' | head -30"
run "gcc $O -fcommon -c sections.c -o sc.o && nm sc.o | grep zeros && readelf -s sc.o | grep zeros"
run "gcc $O -O2 -c hello.c -o h2.o && readelf -S -W h2.o | grep -E 'rodata'"
run "size hello.o bss.o 2>/dev/null; gcc $O -c bss.c && size -A bss.o | head -12"
