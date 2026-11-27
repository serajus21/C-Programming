F="$PWD/../_build/sections/03.08/fedora"; cd "$F" || exit 1
tar xzf ../src2.tgz 2>/dev/null
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "gcc $O fixed.c -o fixed && ./fixed"
run "readelf --debug-dump=info where_g | grep -n -B3 -A3 'DW_AT_frame_base'"
run "objdump -d where | sed -n '/<main>:/,/^\$/p' > a.txt; objdump -d where_g | sed -n '/<main>:/,/^\$/p' > b.txt; cmp a.txt b.txt && echo same-code; size where where_g"
run "gcc $O -c noinclude.c; echo gcc-exit \$?"
run "gcc -std=c23 -O2 -Wall -Wextra -c bugs.c 2>&1 | grep -A4 'uninitialized'"
