F="$PWD/../_build/sections/03.03/fedora"; cd "$F/exp2" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
printf '#include <stdio.h>\n#include <math.h>\nint main(void) {\n    double x = 0.0;\n    printf("%%f\\n", cos(x));\n    return 0;\n}\n' > cosx.c
run "gcc $O -O0 cosx.c -o cosx0"
run "gcc $O -O2 cosx.c -o cosx2 && ./cosx2"
run "gcc $O -O0 -c cosb.c -o cosb.o && nm cosb.o"
