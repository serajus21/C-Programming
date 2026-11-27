F="$PWD/../_build/sections/03.04/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "rpm -q libubsan"
run "cat ub_main.c; gcc $O -fsanitize=undefined -O0 -c ops.c -o ub.o && gcc $O -fsanitize=undefined ub_main.c ub.o -o ub && ./ub"
run "gcc $O -fsanitize=undefined -O2 -c ops.c -o ub2.o && gcc $O -fsanitize=undefined ub_main.c ub2.o -o ub2 && ./ub2"
for L in O0 O2; do run "gcc $O -$L -c ops.c -o p_$L.o && gcc $O ub_main.c p_$L.o -o p_$L && ./p_$L"; done
