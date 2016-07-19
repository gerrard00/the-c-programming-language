#! /bin/zsh

set -e

# this doesn't work for the second call, not sure why.

program=isupper-tests

echo "Test $program\n"
# lm to link math.h
clang -g -Wall -Wextra -Wpedantic $program.c -o $program.o -lm

echo '\n***************'
echo "time"
echo '***************\n'

time ./$program.o "time"

echo '\n***************'
echo "space"
echo '***************\n'

time ./$program.o "space"
