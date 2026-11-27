cd /tmp
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "man gcc 2>/dev/null | col -b | grep -n -A22 '^ *-llibrary' | head -40"
run "man ld 2>/dev/null | col -b | grep -n -A40 '^ *-l namespec' | head -60"
run "man ld 2>/dev/null | col -b | grep -n -A22 '^ *--as-needed' | head -26"
run "man ld 2>/dev/null | col -b | grep -n -B1 -A8 '^ *-y symbol' | head -12"
run "man 5 a.out 2>/dev/null | col -b | sed -n '1,30p'"
run "man ld 2>/dev/null | col -b | grep -n -B2 -A6 'a.out' | head -30"
