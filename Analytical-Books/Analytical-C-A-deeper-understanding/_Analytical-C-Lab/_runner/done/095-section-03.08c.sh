F="$PWD/../_build/sections/03.08/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "readelf --debug-dump=info where_g | grep -n -B2 -A7 ': local\$'"
run "readelf --debug-dump=info where_g | grep -n -A6 'DW_TAG_compile_unit'"
run "readelf --debug-dump=decodedline where_g | head -30"
