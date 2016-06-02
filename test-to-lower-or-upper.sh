#! /bin/zsh

program=to-lower-or-upper
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c -o $program.o

if [[ $? -ne 0 ]]; then
  exit
fi

if [ ! -e to-lower.o ]; then
  ln -s ./$program.o to-lower.o
  echo "made to-lower symlink"
fi

if [ ! -e to-upper.o ]; then
  ln -s ./$program.o to-upper.o
  echo "made to-upper symlink"
fi

echo "\n**********"
echo "lower"
echo "**********"

# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./to-lower.o <<-zzz
NANCY
zzz

echo "\n**********"
echo "upper"
echo "**********"

# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./to-upper.o <<-zzz
lindsay
zzz
