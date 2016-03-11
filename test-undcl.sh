#! /bin/zsh

program=undcl

clear
tmux clear-history

echo "Test $program\n"
gcc -g -Wall -Wextra -Wpedantic $program.c dcl-common.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "default"
echo "**********"

./$program.o <<-zzz 
x () * [] * () char
y * () int
zzz

echo "\n**********"
echo "extra parens"
echo "**********"

./$program.o <<-zzz 
no () * char
no () [] * * int
no [] * () * char
yes * () char
b [] int
yes [] * () bool
zzz
