#! /bin/zsh

set -e

clang -g -Wall -Wextra -Wpedantic fsize.c -o fsize.o


echo "test fsize"

echo "\n\n*****************************"
echo "do it"
echo "*****************************"

./fsize.o ~/junk/foo
