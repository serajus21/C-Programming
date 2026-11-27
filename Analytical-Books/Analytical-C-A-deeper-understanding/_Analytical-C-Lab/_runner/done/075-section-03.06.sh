F="$PWD/../_build/sections/03.06/fedora"; mkdir -p "$F"; cd "$F" || exit 1
tar xzf ../src.tgz
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "gcc $O -c hello.c -o hello.o && gcc $O hello.c -o hello -v 2>&1 | grep collect2 | tr ' ' '\n' | cat -n"
run "gcc -dumpspecs | grep -A2 -E '^\*(startfile|endfile|lib|libgcc|link_gcc_c_sequence):'"
run "rpm -qf /usr/lib64/crt1.o /usr/lib64/crti.o /usr/lib64/crtn.o /usr/lib/gcc/x86_64-redhat-linux/16/crtbegin.o /usr/lib64/libc.so /usr/lib64/libm.so /usr/lib64/libc_nonshared.a"
run "file /usr/lib64/libc.so /usr/lib64/libm.so; cat /usr/lib64/libc.so; echo ----; cat /usr/lib64/libm.so"
run "ls -l /usr/lib/gcc/x86_64-redhat-linux/16/ | grep -E 'libgcc|crt'; cat /usr/lib/gcc/x86_64-redhat-linux/16/libgcc_s_asneeded.so 2>/dev/null; cat /usr/lib/gcc/x86_64-redhat-linux/16/libgcc_s.so 2>/dev/null"
run "ar t /usr/lib64/libc_nonshared.a"
for f in /usr/lib64/crt1.o /usr/lib64/crti.o /usr/lib/gcc/x86_64-redhat-linux/16/crtbegin.o /usr/lib/gcc/x86_64-redhat-linux/16/crtend.o /usr/lib64/crtn.o; do run "nm $f; size -A $f | grep -v '^$'"; done
run "objdump -d /usr/lib64/crti.o /usr/lib64/crtn.o | grep -v '^$'"
run "objdump -dr /usr/lib64/crt1.o | grep -v '^$'"
run "gcc -print-file-name=libc.so; gcc -print-file-name=crt1.o; gcc -print-file-name=libm.a; gcc -print-search-dirs | sed -n '1,2p'"
run "ld --verbose | grep -n -E 'SEARCH_DIR|SEGMENT_START|SIZEOF_HEADERS|ENTRY|OUTPUT_FORMAT' | head -20"
run "gcc $O hello.o -o hello_map -Wl,-Map=hello.map && cmp hello hello_map; grep -n -E '^ \\.(text|init|plt|rodata|fini|interp)|^\\.(text|init|plt|rodata|fini|interp|data|bss)|hello.o|crt1.o|crti.o|crtn.o|crtbegin.o|crtend.o' hello.map | head -80"
