#! /bin/zsh

program=count-c-keywords
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "default"
echo "**********"

./$program.o <<-zzz 
int main() {
  int x = 7;
  int y = 10;
  char my_char = 'a';

  while(x < 10) {
    x++;
  }
}

void foo(int bar) {
}
zzz

echo "\n**********"
echo "One char, one char in underscore"
echo "**********"

./$program.o <<-zzz 
char my_char = 'a';
zzz
