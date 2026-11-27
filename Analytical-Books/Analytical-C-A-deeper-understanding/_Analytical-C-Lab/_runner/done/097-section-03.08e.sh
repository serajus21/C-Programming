F="$PWD/../_build/sections/03.08/fedora"; cd "$F" || exit 1
tar xzf ../src3.tgz 2>/dev/null
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
G="gdb -batch -nx -ex 'set debuginfod enabled off'"
run "gcc $O brace.c -o brace"
run "gcc $O -O2 bugs.c -o bugs2 2>&1 | sed -n '/uninitialized/,+0p;/inlined/,+0p'; gcc $O -O2 -c bugs.c 2>&1 | grep -B3 -A6 'is used uninitialized'"
run "for o in -O0 -O1 -O2 -O3 -Og; do printf '%s: ' \$o; gcc -std=c23 -Wall -Wextra \$o -c bugs.c 2>&1 | grep -c 'warning:'; done"
run "gcc -std=c23 -Wall -O0 -c unin.c"
run "gcc $O -g -DSTAGE=4 phases.c -o p4g"
run "gcc $O pedantic.c -o ped && ./ped; gcc -std=c23 -pedantic pedantic.c -o ped2"
run "gcc $O fixed.c -o fixed && ./fixed"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -Wall -Wextra -pedantic avr_warn.c -o avr_warn.elf; grep -n 'define F_CPU' /usr/avr/include/util/delay.h"
run "$G -ex 'break main' -ex run -ex 'info locals' -ex next -ex next -ex 'info locals' ./where_g2 2>&1 | grep -v -E 'debuginfod|^ *<|^This GDB|^Enable|^To make|thread'"
run "man gcc 2>/dev/null | col -b | grep -n -B1 -A3 -E 'Because these warnings depend on optimization|only possible in optimizing compilation'"
run "gcc -std=c23 -Wall -Wextra -c bugs.c 2>&1 | grep -c warning; gcc -std=c23 -Wall -c bugs.c 2>&1 | grep -c warning"
