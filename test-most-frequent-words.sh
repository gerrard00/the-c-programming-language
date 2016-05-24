#! /bin/zsh

program=most-frequent-words
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c binary-tree.c getword.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "default"
echo "**********"

# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./$program.o <<-zzz
It was the best of times, it was the worst of times,
it was the age of wisdom, it was the age of foolishness,
it was the epoch of belief, it was the epoch of incredulity,
it was the season of Light, it was the season of Darkness,
it was the spring of hope, it was the winter of despair,
we had everything before us, we had nothing before us,
we were all going direct to Heaven, we were all going direct
the other way – in short, the period was so far like the present
period, that some of its noisiest authorities insisted on its
being received, for good or for evil, in the superlative degree
of comparison only. fuck
zzz

# echo "\n**********"
# echo "stupid"
# echo "**********"

# # valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
# ./$program.o <<-zzz
# we are are are here here
# zzz
