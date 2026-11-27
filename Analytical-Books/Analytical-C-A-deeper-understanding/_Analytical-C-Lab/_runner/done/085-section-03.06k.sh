F="$PWD/../_build/sections/03.06/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
G=/usr/lib/gcc/x86_64-redhat-linux/16
run "objdump -dr $G/crtbegin.o | grep -v '^\$' | sed -n '1,80p'"
run "readelf -d /lib64/libc.so.6 | grep SONAME; readelf -d /lib64/libm.so.6 | grep SONAME"
run "cat $G/libatomic_asneeded.so $G/libatomic.so"
run "ld -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o hello_byhand4 /usr/lib64/crt1.o /usr/lib64/crti.o $G/crtbegin.o -L$G -L/usr/lib64 hello.o -lgcc -lgcc_s_asneeded -latomic_asneeded -lc -lgcc -lgcc_s_asneeded $G/crtend.o /usr/lib64/crtn.o && ./hello_byhand4 && ls -l hello_byhand4 && cmp hello hello_byhand4 | head -1"
run "gcc $O -static hello.c -o hs -Wl,-Map=hs.map && sed -n '/^Archive member included/,/^\$/p' hs.map | grep -c '^[^ ].*libc\\.a('"
run "gcc $O -static hello.c -o hs -Wl,-t,-t | grep -c 'libc\\.a'"
run "objdump -d -j .plt hello | sed -n '/puts@plt-0x10/,/^\$/p'; readelf -x .got.plt hello"
run "gcc $O -Wl,--as-needed -lm cube.c -o cube3 -Wl,-y,cbrt"
run "gcc $O -static -lm cube.c -o cube5 -Wl,-y,cbrt"
run "objdump -dr /usr/lib64/crt1.o | grep -E 'GOTPCRELX'"
