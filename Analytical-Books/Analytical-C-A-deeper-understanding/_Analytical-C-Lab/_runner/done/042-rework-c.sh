F="$PWD/../_build/sections/03.02/fedora/rw"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
printf '#include <stdio.h>\rint main(void) {\r    printf("cr\\n");\r    return 0;\r}\r' > cr.c
run "file cr.c; gcc -std=c23 -Wall -Wextra -pedantic cr.c -o cr && ./cr"
run "time (gcc -std=c23 -c hello.c -o /dev/null)"
