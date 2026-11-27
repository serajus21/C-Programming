F="$PWD/../_build/sections/03.06/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "gcc $O -static hello.c -o hs -Wl,-t,-t | grep -c 'libc\\.a('; gcc $O -static hello.c -o hs -Wl,-t,-t | grep 'libc\\.a(' | head -3"
run "sed -n '1,8p' hs.map; awk '/^Archive member included/{f=1;next} /^Discarded|^There are no discarded|^Memory Configuration/{f=0} f' hs.map | grep -c '^[^ ].*libc\\.a('"
