F="$PWD/../_build/sections/03.04/fedora"; mkdir -p "$F/d2"; cd "$F/d2" || exit 1; cp ../hello.c ../ops.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "gcc -std=c23 -O0 -fdump-tree-lower -fdump-rtl-final -S hello.c && ls"
run "grep -c '' hello.c.*r.final; grep -n -E 'insn|call_insn' hello.c.*r.final | head -20"
run "gcc -std=c23 -O2 -S -fno-asynchronous-unwind-tables ops.c -o - | grep -c ''"
run "gcc -std=c23 -O2 -fdump-passes -c ops.c -o /dev/null 2>&1 | grep -c -E 'ON|OFF'; gcc -std=c23 -O2 -fdump-passes -c ops.c -o /dev/null 2>&1 | grep -c 'ON'"
run "gcc -std=c23 -O0 -fdump-passes -c ops.c -o /dev/null 2>&1 | grep -c 'ON'"
run "printf 'unsigned d3(unsigned x){return x/3;}\nunsigned d7(unsigned x){return x/7;}\nint s10(int x){return x/10;}\n' > div.c; gcc -std=c23 -O2 -S -fno-asynchronous-unwind-tables div.c -o - | grep -v -E '^\\s*\\.(file|ident|section|text|p2align|globl|type|size|align|long|string)|^[0-4]:'"
