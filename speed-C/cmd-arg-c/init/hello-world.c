#include<stdio.h>
int main(int _arg_count, char *_arg_list[]) {
    // printf("Total Arguments recieved: %d\n", _arg_count);

    for(int _arg_index=0; _arg_index<_arg_count; _arg_index++) {
        // printf("Argument _arg_list[%d]: %s\n", _arg_index, _arg_list[_arg_index]);
        printf("%s\n", _arg_list[1]);
    }
}