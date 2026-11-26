cd "$PWD/../_build/sections/03.01/fedora" || exit 1
clang -std=c23 -fsyntax-only -Xclang -dump-tokens hello.c 2>&1 | grep 'hello.c:' | tr -s ' '
