#! /bin/zsh

program=count-variable-names
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic $program.c binary-tree.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "stupid, just names"
echo "**********"

./$program.o 6 <<-zzz 
int abcdedad;
/* this is a comment with my name gerrarj misspelled */
int gerrard;
int abcdedead;
int abcdedifferent;
int abcdefferent;
char *test = "this is a string with my name gerrarr misspelled";
zzz
