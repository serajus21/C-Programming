F="$PWD/../_build/sections/03.05/fedora"; cd "$F" || exit 1
echo '$ readelf -S hello.o'; readelf -S hello.o; echo "[exit $?]"
echo '$ readelf -r hello.o'; readelf -r hello.o; echo "[exit $?]"
