F="$PWD/../_build/sections/03.05/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "nm hello | grep -w -E '_start|main'"
run "gcc -std=c23 hello.c -o hello -### 2>&1 | grep -o -E '[^ ]*crt[a-z0-9]*\\.o' | tr '\\n' ' '"
