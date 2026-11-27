F="$PWD/../_build/sections/03.06/fedora"; cd "$F" || exit 1
cp ../extra/avr_div.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
G=/usr/lib/gcc/x86_64-redhat-linux/16
run "readelf -S -W $G/crtbegin.o | grep -E ' \\.text|Al'; readelf -S -W hello.o | grep -E ' \\.text|Al'"
run "ld --help | grep -A2 -E 'separate-code'"
run "man gcc 2>/dev/null | col -b | sed -n '1248,1262p'"
run "gcc $O -c greet_def.c && gcc greet_def.o -o nomain"
run "nm $G/libgcc.a 2>/dev/null | grep -E ' T (__divti3|__udivti3|__popcountdi2)\$'"
run "cmp hello ao/a.out && echo identical"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -Wall avr_div.c -o avr_div.elf -Wl,-Map=avr_div.map && sed -n '1,12p' avr_div.map && avr-objdump -d avr_div.elf | grep -E 'call.*udivmod'"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -c avr_div.c && avr-objdump -dr avr_div.o | grep -A1 call"
run "avr-objdump -d avr_hello.elf | sed -n '/<__vectors>:/,/<__ctors_end>/p' | sed -n '2,5p;26,28p'"
run "avr-objdump -d avr_hello.elf | sed -n '/<__bad_interrupt>:/,/<main>/p'; avr-objdump -d avr_hello.elf | sed -n '/^0000008a/,/^00000092/p'"
run "avr-gcc -mmcu=atmega328p -dumpspecs 2>/dev/null | grep -A1 -E '^\\*(lib|link_gcc_c_sequence|startfile):'"
run "readelf -n hello | grep -A1 'Build ID'"
