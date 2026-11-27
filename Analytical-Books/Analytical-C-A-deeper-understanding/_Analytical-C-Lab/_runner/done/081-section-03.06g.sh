F="$PWD/../_build/sections/03.06/fedora"; cd "$F" || exit 1
cp ../extra/nostart.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "ld -o h2 /usr/lib64/crt1.o hello.o -lc; readelf -l h2 | grep interpreter; ./h2"
run "ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o h3 /usr/lib64/crt1.o hello.o -lc && ./h3 && ls -l h3 && nm h3 | grep -c ."
run "gcc $O -nostartfiles nostart.c -o nostart && ./nostart; echo status \$?; nm nostart | grep -E ' (T|U) '"
run "gcc $O -nostartfiles hello.c -o hello_ns"
run "gcc $O -static hello.c -o hs -Wl,--trace | grep -c 'libc.a('; gcc $O -static hello.c -o hs -Wl,--trace | grep 'libc.a(' | head -8"
run "gcc $O -static hello.c -o hs -Wl,-y,puts -Wl,-y,_IO_puts"
run "nm cube1 | grep -E ' U '; nm cube.o 2>/dev/null | grep printf"
run "objdump -d cube1 | grep -E 'call.*(printf|cbrt|strtod)'"
run "objdump -d hello_static | sed -n '/<main>:/,/^\$/p'"
