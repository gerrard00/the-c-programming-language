#! /bin/zsh
echo "Test $1"
clang -g -Wall -Wextra -Wpedantic $1.c -o $1.o &&./$1.o
# exec "cc $1.c -o $1.o && ./$1.o"

