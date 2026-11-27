F="$PWD/../_build/sections/03.05/fedora"; mkdir -p "$F/x"; cd "$F/x" || exit 1; cp ../*.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "readelf -h /bin/ls /lib64/libc.so.6 | grep -E 'File|Type'"
run "gcc $O -c hello.c -o hello.o && cp hello.o s.o && strip s.o && nm s.o; readelf -S -W s.o | grep -c '\\]'; gcc s.o -o s"
run "cp hello.o su.o && strip --strip-unneeded su.o && nm su.o && gcc su.o -o su && ./su"
run "sed 's/zeros\\[0\\]/zeros[5]/; s/    return elsewhere;/    counter = 7;\\n    return elsewhere;/' sections.c > sections3.c && gcc $O -c sections3.c -o s3.o && readelf -r -W s3.o | grep -E 'zeros|counter'"
run "gcc $O -fPIE -c hello.c -o hpie.o && readelf -r -W hpie.o"
run "objdump -s -j .comment hello.o | tail -3; gcc $O hello.c -o hello && readelf -p .comment hello"
run "printf 'int counter = 1;\nint elsewhere = 0;\n' > else2.c && gcc $O -c sections.c && gcc $O sections.o else2.c -o s4"
