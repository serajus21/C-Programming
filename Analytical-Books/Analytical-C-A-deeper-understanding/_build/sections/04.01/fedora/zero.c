#include <stdio.h>
int main(void) {
    printf("[%#x] [%#o] [%#b] [%#x] [%#B]\n", 0u, 0u, 0u, 255u, 5u);
    printf("%s %s\n", _Generic(3735928559, int: "int", long: "long", unsigned: "unsigned", default: "other"),
                      _Generic(0xDEADBEEF, int: "int", long: "long", unsigned: "unsigned", default: "other"));
}
