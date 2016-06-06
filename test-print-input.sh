#! /bin/zsh

program=print-input
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c -o $program.o

if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "non-graphic"
echo "**********"

echo 'this has a bell \a and a tab \t right here.' | ./$program.o

echo "\n**********"
echo "long"
echo "**********"

echo 'this is a really long line with no breaks that really needs to wrap at least a little bit.' | ./$program.o
