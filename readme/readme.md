This small project provides a 64-bit NASM (Intel syntax) implementation of ft_strlen
and a C test program that links against the static library libasm.a.

How to build and run:

    nasm -f elf64 ft_strlen.s -o ft_strlen.o
    ar rcs libasm.a ft_strlen.o
    gcc -c main.c -o main.o
    gcc main.o libasm.a -o test
    ./test

Notes:
- Implementation follows the System V AMD64 calling convention: first argument in RDI,
  return value in RAX (size_t is 64-bit).
- No syscalls occur inside ft_strlen, so errno handling is not required here. If you
  implement syscalls elsewhere, check return values and set errno via ___error or
  errno_location as requested.
- The assembler file uses NASM/Intel syntax and must be assembled with nasm.
