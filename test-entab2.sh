#! /bin/zsh

program=entab2

echo "Test $program\n"
clang -g -Wall -Wextra -Wpedantic $program.c -o $program.o && ./$program.o 8 16 24


