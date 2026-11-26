F="$PWD/../_build/sections/03.02/fedora/rw"; cd "$F" || exit 1
mkdir -p dumps && cp hello.c dumps/ && cd dumps
gcc -std=c23 -fdump-tree-all -c hello.c -o /dev/null
echo "== first dump mentioning puts:"; grep -l 'puts' hello.c.* | sort | head -3
echo "== dumps mentioning printf (call):"; grep -l 'printf (' hello.c.* | sort | tail -2
cd ..
echo "== ebcdic block"
for c in "cat ebc.c nl.c hx.c" "gcc -std=c23 ebc.c -o ebc && ./ebc; echo \$?" "gcc -std=c23 -fexec-charset=IBM1047 ebc.c -o ebc2 && ./ebc2; echo \$?" "gcc -std=c23 -fexec-charset=IBM1047 nl.c -o nl && ./nl; echo \$?" "gcc -std=c23 -fexec-charset=IBM1047 hx.c -o hx && ./hx; echo \$?"; do printf '$ %s\n' "$c"; bash -c "$c" 2>&1; done
