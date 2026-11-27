F="$PWD/../_build/sections/03.06/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "gcc $O hello.o -o hmove -Wl,-Ttext-segment=0x800000 && ./hmove && nm hmove | grep -w -E 'main|_start' && objdump -d hmove | sed -n '/<main>:/,/^\$/p'"
run "gcc $O hello.o -o hnosep -Wl,-z,noseparate-code && nm hnosep | grep -w main && readelf -l hnosep | grep -c LOAD"
run "objdump -d --disassemble=_start hello | grep -v '^\$'"
run "objdump -d -j .init hello | grep -v '^\$'"
run "readelf -l hello | sed -n '/Section to Segment/,\$p'"
