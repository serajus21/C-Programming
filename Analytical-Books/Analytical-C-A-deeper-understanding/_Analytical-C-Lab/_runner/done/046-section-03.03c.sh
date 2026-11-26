F="$PWD/../_build/sections/03.03/fedora"; cd "$F" || exit 1
for n in 204 218 226 267; do s=$((n-2)); e=$((n+1)); echo "== $n"; sed -n "${s},${e}p" hello.i; done
echo "== O2"; gcc -std=c23 -O2 -E hello.c | sed -n 565,590p
