#! /bin/zsh
echo "Test $1\n"
clang -g -Wall -Wextra -Wpedantic $1.c -o $1.o &&./$1.o

mkfifo mypipe
./$1.o < mypipe &

echo "1 2 - 4 5 + *"
echo "1 2 - 4 5 + *" > mypipe

echo "1 2 *"
echo "1 2 *" > mypipe

rm mypipe

echo
echo "done!"
