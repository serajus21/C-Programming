F="$PWD/../_build/sections/03.03/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "gcc -std=c23 -E hello.c -o hello.i && head -12 hello.i"
run "grep -n -E '\\) *\\{|^\\{' hello.i"
run "gcc -std=c23 -O2 -E hello.c | grep -n -E '__extern_inline|__inline' | cut -c1-120"
run "grep -n -E 'define (PB5|PORTB5|DDB5) ' /usr/avr/include/avr/portpins.h /usr/avr/include/avr/iom328p.h"
run "sed -n 560,573p hello.i"
run "grep -c '' /usr/include/stdio.h; grep -c -E '^\\s*(/\\*|\\*|//)' /usr/include/stdio.h"
run "gcc -std=c23 -E -dI hello.c | grep -n '#include' | head -5"
