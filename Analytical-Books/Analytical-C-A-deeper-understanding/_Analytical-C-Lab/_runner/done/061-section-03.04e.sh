F="$PWD/../_build/sections/03.04/fedora"; cd "$F" || exit 1; cp ../divcost.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "grep -m1 'model name' /proc/cpuinfo"
run "gcc $O -O2 divcost.c -o divcost && ./divcost && ./divcost"
run "gcc $O -O2 -S divcost.c -o - | grep -E 'divl|imulq'"
