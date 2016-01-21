#! /bin/zsh
echo "Test $1"
clang -g -Wall -Wextra -Wpedantic $1.c -o $1.o 

mkfifo mypipe
./$1.o < mypipe &

echo  "no way" > mypipe
echo  "could" > mypipe
echo "not a match bro" >mypipe
echo "this could be could really be" > mypipe
echo "this won't be" > mypipe
echo "this would be" > mypipe
echo > mypipe

rm mypipe

echo
echo "done!"
