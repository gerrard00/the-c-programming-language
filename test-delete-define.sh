#! /bin/zsh

program=test-delete-define
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c table-lookup.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "delete"
echo "**********"

# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./$program.o <<-zzz
zzz
