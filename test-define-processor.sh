#! /bin/zsh

program=define-processor
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
#define GERRARD 38
#define NANCY 4
zzz

# echo "\n**********"
# echo "stupid"
# echo "**********"

# # valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
# ./$program.o <<-zzz
# we are are are here here
# zzz
