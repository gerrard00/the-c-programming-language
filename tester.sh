#! /bin/zsh
echo "Test $1"
cc $1.c -o $1.o &&./$1.o
# exec "cc $1.c -o $1.o && ./$1.o"

