run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "man gcc 2>/dev/null | col -b | sed -n '15216,15232p'"
run "man gcc 2>/dev/null | col -b | grep -n -B1 -A6 '^ *-o file' | head -20"
