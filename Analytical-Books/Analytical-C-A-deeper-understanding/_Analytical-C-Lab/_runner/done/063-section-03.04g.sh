F="$PWD/../_build/sections/03.04/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "rpm --eval '%{optflags}'"
printf '#include <stdio.h>\nint main(void) {\n    int n = 7;\n    printf(\"%%d\\\\n\", n);\n    return 0;\n}\n' > one_int.c
run "cat one_int.c; gcc $O -S -fno-asynchronous-unwind-tables one_int.c -o - | grep -E 'eax|call'"
run "cp ../../03.03/root.c . && gcc $O -S -fno-asynchronous-unwind-tables root.c -o - | grep -E 'eax|call'"
run "diff <(gcc $O -O2 -S -fno-asynchronous-unwind-tables ops.c -o -) <(gcc $O -O2 -fno-omit-frame-pointer -S -fno-asynchronous-unwind-tables ops.c -o -) && echo identical"
run "gcc $O -O3 -S -fno-asynchronous-unwind-tables ops.c -o - | sed -n '/^sum_to:/,/\\.size/p' | grep -c -v -E '^\\s*\\.(size|p2align)'"
run "gcc $O -O2 -S -fno-asynchronous-unwind-tables ops.c -o o2.s && gcc $O -O2 -c ops.c -o o2.o && objdump -d o2.o | sed -n '/<div10>:/,/ret/p'"
