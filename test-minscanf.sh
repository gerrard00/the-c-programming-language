#! /bin/zsh

program=minscanf
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c -o $program.o

if [[ $? -ne 0 ]]; then
  exit
fi

echo "Gerrard A Lindsay 38 217.8" | ./$program.o
