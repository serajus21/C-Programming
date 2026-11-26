F="$PWD/../_build/sections/03.03/fedora"; mkdir -p "$F/exp2"; cd "$F/exp2" || exit 1
cp ../hello.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
printf '#include <stdio.h>\nint main(void) {\n    printf("%%f\\n", cos(0.0));\n    return 0;\n}\n' > cosa.c
printf '#include <stdio.h>\n#include <math.h>\nint main(void) {\n    printf("%%f\\n", cos(0.0));\n    return 0;\n}\n' > cosb.c
run "gcc $O cosa.c -o cosa -lm"
run "gcc $O -O0 cosb.c -o cosb"
run "gcc $O -O2 cosb.c -o cosc && ./cosc"
mkdir -p inc; echo '#error this is not the real stdio.h' > inc/stdio.h
run "gcc $O -Iinc hello.c -o h1"
run "gcc $O -idirafter inc hello.c -o h2 && ./h2"
printf 'int a[] = {\n#include "nums.txt"\n};\n#include <stdio.h>\nint main(void) { printf("%%zu\\n", sizeof a / sizeof a[0]); return 0; }\n' > arr.c; echo '1, 2, 3, 4' > nums.txt
run "gcc $O arr.c -o arr && ./arr"
