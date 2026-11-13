# Arithmetic memory map

Build with `make`, then run `./arithmetic` and enter an operation and two integers.
After the inputs, the program lists the addresses, current values, and sizes of
the parameters in `calculate`, followed by the variables in `main` after the
calculation, then prints the arithmetic
result. `memory_map.c` is the display module; `memory_map.h` defines its interface.

These are virtual addresses in the running process. They may change between runs
because of address space layout randomization. The size of a pointer parameter
is the size of the pointer itself; its Value column shows the address it holds.
`integer_result` and `division_result` in
`main` show the storage of the values those pointers refer to. The two `left`
and `right` entries belong to different function calls and occupy distinct
storage. The listing covers the arithmetic program's named variables and
parameters while they are alive, rather than every object used internally by
the C library or the operating system.
