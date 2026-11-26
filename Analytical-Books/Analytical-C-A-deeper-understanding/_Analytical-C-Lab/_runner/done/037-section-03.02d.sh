F="$PWD/../_build/sections/03.02/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
printf '#include <stdio.h>\n#define GREETING "hello, " \\\n"world\\n"\nint main(void) { printf(GREETING); return 0; }\n' > e1.c
printf '#include <stdio.h>\n#define GREETING "hello, "\n"world\\n"\nint main(void) { printf(GREETING); return 0; }\n' > e1b.c
run "cat e1.c; gcc $O e1.c -o e1 && ./e1"
run "cat e1b.c; gcc $O e1b.c -o e1b"
for v in '0x1E+1' '0x1E + 1' '0x1F+1' '1e+1' '1.5.2' '08' '0b101'; do printf 'int x = %s;\n' "$v" > e2.c; run "cat e2.c; gcc $O -c e2.c -o e2.o && echo compiled"; done
printf '#include <stdio.h>\nvoid greet(void) { puts("hello from greet"); }\n' > greet_def.c
run "gcc $O -c greet.c && gcc $O -c greet_def.c && gcc greet.o greet_def.o -o greet && ./greet"
run "gcc -v -std=c23 hello.c -o hello 2>&1 | sed -n '/search starts here/,/End of search/p'"
run "gcc -### hello.c 2>&1 | grep -c 'search starts'"
