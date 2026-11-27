run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "man 2 execve 2>/dev/null | col -b | sed -n '/^DESCRIPTION/,/^RETURN VALUE/p' | head -60"
run "man 2 execve 2>/dev/null | col -b | grep -n -B2 -A8 'PT_INTERP'"
run "man 8 ld.so 2>/dev/null | col -b | sed -n '/^DESCRIPTION/,+12p'"
run "man 8 ld.so 2>/dev/null | col -b | grep -n -A8 '^ *LD_BIND_NOW'"
run "man 7 vdso 2>/dev/null | col -b | sed -n '/^DESCRIPTION/,+14p'"
run "man 3 getauxval 2>/dev/null | col -b | grep -n -A4 -E '^ *AT_(ENTRY|BASE|PHDR|RANDOM|SYSINFO_EHDR)'"
