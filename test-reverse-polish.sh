#! /bin/zsh

echo "Test $1\n"
clang -g -Wall -Wextra -Wpedantic -lm $1.c -o $1.o &&./$1.o || exit 1

mkfifo mypipe
./$1.o < mypipe &

echo "1 2 - 4 5 + *"
echo "1 2 - 4 5 + *" > mypipe

echo "1 2 *"
echo "1 2 *" > mypipe

echo "45 @sin"
echo "45 @sin" > mypipe

echo "3 @exp"
echo "3 @exp" > mypipe

echo "2 3 @pow"
echo "2 3 @pow" > mypipe

rm mypipe

echo
echo "done!"
