#! /bin/zsh

program=count-variable-names
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c binary-tree-with-key.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "stupid, just names"
echo "**********"

./$program.o <<-zzz 
abcdefgerrard
abcdifferent
abcdeflindsay
zzz
