F="$PWD/../_build/sections/03.03/fedora"; mkdir -p "$F/exp"; cd "$F/exp" || exit 1
cp ../body.txt .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
printf '#include <stdio.h>\nint main(void) {\n#include "body.txt"\n#include "body.txt"\n    return 0;\n}\n' > twice.c
run "gcc $O twice.c -o twice && ./twice"
printf 'int counter = 0;\n' > def.h; printf 'extern int counter;\n' > decl.h
printf '#include "def.h"\n#include "def.h"\nint main(void) { return counter; }\n' > d2.c
printf '#include "decl.h"\n#include "decl.h"\nint counter = 3;\nint main(void) { return counter; }\n' > e2.c
run "gcc $O d2.c -o d2"
run "gcc $O e2.c -o e2 && ./e2; echo \$?"
printf '#include <stdio.h>\n#define SQUARE(x) x * x\nint main(void) {\n    printf("%%d\\n", 100 / SQUARE(5));\n    return 0;\n}\n' > sq.c
run "cat sq.c; gcc $O sq.c -o sq && ./sq; gcc -std=c23 -E -P sq.c | tail -4"
printf '#include <stdio.h>\n#include <stdlib.h>\n#include <math.h>\nint main(int argc, char *argv[]) {\n    if (argc < 2) return 1;\n    printf("%%f\\n", sqrt(atof(argv[1])));\n    return 0;\n}\n' > root3.c
run "gcc $O -O2 root3.c -o root3"
run "gcc $O -O2 -S root3.c -o - | grep -E 'sqrt|call'"
run "gcc $O -O2 -fno-math-errno -S root3.c -o - | grep -E 'sqrt|call'; gcc $O -O2 -fno-math-errno root3.c -o root3b && ./root3b 2"
run "printf '#include <stdlib.h>\n' | gcc -std=c23 -E - | wc -l; printf '#include <stdlib.h>\n' | gcc -std=c23 -E - | grep -c '^# '"
run "diff <(gcc -std=c17 -dM -E - </dev/null | sort) <(gcc -std=c23 -dM -E - </dev/null | sort)"
run "grep -rn 'define EOF' /usr/include/stdio.h"
