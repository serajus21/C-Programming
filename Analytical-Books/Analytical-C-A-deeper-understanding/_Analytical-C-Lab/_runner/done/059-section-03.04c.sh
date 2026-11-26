F="$PWD/../_build/sections/03.04/fedora"; cd "$F" || exit 1
echo '$ gcc -std=c23 -Wall -Wextra -pedantic -S -masm=intel hello.c -o hello_intel.s'
gcc -std=c23 -Wall -Wextra -pedantic -S -masm=intel hello.c -o hello_intel.s; echo "[exit $?]"
cat -A hello_intel.s | sed -n 1,30p
