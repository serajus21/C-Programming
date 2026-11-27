F="$PWD/../_build/sections/03.06/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "nm hello_ns | grep -w main; ./hello_ns; echo status \$?"
run "gcc $O -static hello.c -o hs -Wl,--trace | grep -c 'libc.a'; gcc $O -static hello.c -o hs -Wl,--trace | grep 'libc.a' | head -5"
