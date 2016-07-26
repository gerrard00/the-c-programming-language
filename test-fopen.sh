#! /bin/zsh

set -e

clang -g -Wall -Wextra -Wpedantic fopen.c -o fopen.o
clang -g -Wall -Wextra -Wpedantic fopen-fields.c -o fopen-fields.o

echo "test fopen\n\n"
time ./fopen.o 1> /dev/null
echo "\ntest fopen-fields\n\n"
time ./fopen-fields.o 1> /dev/null

