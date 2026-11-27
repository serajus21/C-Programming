F="$PWD/../_build/sections/03.08/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
G="gdb -batch -nx -ex 'set debuginfod enabled off'"
run "cat -n where.c"
run "gcc $O where.c -o where && gcc $O -g where.c -o where_g && ls -l where where_g && readelf -S -W where_g | grep -E 'debug'"
run "$G -ex 'break main' -ex run -ex next -ex 'info locals' -ex 'p &local' -ex 'info line' ./where_g 2>&1 | grep -v -E 'debuginfod|^ *<|^This GDB|^Enable|^To make|thread'"
run "$G -ex 'break main' -ex run -ex 'info locals' ./where 2>&1 | grep -v -E 'debuginfod|^ *<|^This GDB|^Enable|^To make|thread'"
run "readelf --debug-dump=info where_g | grep -B1 -A8 'DW_AT_name *: local'"
run "objdump -d where_g | sed -n '/<main>:/,/^\$/p' | head -12"
run "gcc $O -g -O2 where.c -o where_g2 && $G -ex 'break main' -ex run -ex 'info locals' ./where_g2 2>&1 | grep -v -E 'debuginfod|^ *<|^This GDB|^Enable|^To make|thread'"
run "gcc -std=c23 -fanalyzer -c bugs.c 2>&1 | grep -E 'warning:'"
run "gcc $O -Wshadow -Wconversion -c bugs.c 2>&1 | grep -c 'warning:'"
run "gcc -std=c23 -Wall -Wextra -c bugs.c; echo gcc-exit \$?; gcc -std=c23 -Wall -Wextra -Werror -c bugs.c 2>/dev/null; echo gcc-exit \$?; gcc -std=c23 -c cascade.c 2>/dev/null; echo gcc-exit \$?"
