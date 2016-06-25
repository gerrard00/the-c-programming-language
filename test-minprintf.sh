#! /bin/zsh

program=minprintf
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c -o $program.o

if [[ $? -ne 0 ]]; then
  exit
fi

./$program.o
