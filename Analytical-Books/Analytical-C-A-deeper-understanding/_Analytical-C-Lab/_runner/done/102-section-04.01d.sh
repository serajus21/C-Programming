F="$PWD/../_build/sections/04.01/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "od -t o1 bytes.bin"
run "printf '%x\n' \$((~0x39)); printf 'int main(void){return 0;}\n' > perm_new.c; stat -c '%a %A' perm_new.c; umask"
run "ls -lh /usr/bin/bash | awk '{print \$5}'; free -h | head -2"
run "cat zero.c"
