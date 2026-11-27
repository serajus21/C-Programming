F="$PWD/../_build/sections/04.01/fedora"; cd "$F" || exit 1
cp ../hexdump_me.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "gcc -std=c23 -Wall -Wextra -pedantic hexdump_me.c -o hexdump_me && rm -f bytes.bin && ./hexdump_me && xxd bytes.bin && od -A d -t o1 bytes.bin && od -A x -t x1 bytes.bin && od -A d -t d1 bytes.bin"
run "for f in ../*.c; do cmp -s \$f \$(basename \$f) && echo \"same \$f\" || echo \"DIFF \$f\"; done"
