F="$PWD/../_build/sections/03.02/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
printf '// tri.c\n// Trigraphs: removed from the language in C23.\n#include <stdio.h>\n\nint main(void) {\n    printf("Is it true??!\\n");\n    return 0;\n}\n' > tri.c
run "cat tri.c"
run "gcc -std=c17 -Wall -Wextra -pedantic tri.c -o tri17 && ./tri17"
run "gcc -std=c23 -Wall -Wextra -pedantic tri.c -o tri23 && ./tri23"
run "printf '#include <stdio.h>\r\nint main(void) {\r\n    printf(\"crlf\\\\n\");\r\n    return 0;\r\n}\r\n' > crlf.c; file crlf.c; gcc -std=c23 -Wall -Wextra -pedantic crlf.c -o crlf && ./crlf"
run "clang -### -std=c23 hello.c -o hello_clang 2>&1 | grep -E '^ \"' | cut -c1-140"
run "clang -std=c23 hello.c -o hello_clang && ./hello_clang"
run "printf 'int main(void){ return 0; }' > nonl.c; gcc -std=c23 -Wall -Wextra -pedantic nonl.c -o nonl; echo built"
run "printf 'int main(void){ return 0x1F+1; }\n' > f.c; gcc -std=c23 f.c -o f && ./f; echo \$?"
run "gcc -std=c23 -E -P escape.c | tail -6"
run "gcc -std=c23 -ftime-report -c hello.c 2>&1 | head -12"
