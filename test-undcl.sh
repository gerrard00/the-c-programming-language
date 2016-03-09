#! /bin/zsh

program=undcl

clear
tmux clear-history

echo "Fuck Test $program\n"
gcc -g -Wall -Wextra -Wpedantic $program.c dcl-common.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "default"
echo "**********"

./$program.o <<-zzz 
x () * [] * () char
zzz
