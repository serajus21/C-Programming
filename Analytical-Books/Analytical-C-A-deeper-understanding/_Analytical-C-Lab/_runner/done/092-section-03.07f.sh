F="$PWD/../_build/sections/03.07/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
G="gdb -batch -nx -ex 'set debuginfod enabled off'"
run "nm -D /lib64/libc.so.6 | grep -E ' (puts|__libc_start_main)@@'"
run "grep -m1 'model name' /proc/cpuinfo"
run "nm where_pie | grep -w main; readelf -d /lib64/libc.so.6 | grep -E 'RELR|RELACOUNT'; LD_DEBUG=statistics ./where_pie 2>&1 | grep -E 'relative|number of relocations'"
run "readelf --dyn-syms where | grep -w puts; readelf --dyn-syms where_pie | grep -w puts"
run "ls -ld /lib64"
run "avr-objdump -dr /usr/avr/lib/avr5/crtatmega328p.o | sed -n '/init9/,\$p' | head -12"
run "$G -ex 'break __vdso_clock_gettime' -ex run -ex bt ./clock 2>&1 | grep -E '^#|Breakpoint 1,'"
run "env -i ./stack | head -4"
