F="$PWD/../_build/sections/03.05/fedora"; cd "$F/y" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
printf 'double scale(double x) { return x * 2.5; }\n' > cst.c
run "cat cst.c; gcc -std=c23 -Wall -Wextra -pedantic -O2 -c cst.c && readelf -S cst.o | grep -A1 rodata && readelf -r cst.o | grep -v '^$' && objdump -s -j .rodata.cst8 cst.o | tail -1"
