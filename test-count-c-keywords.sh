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

echo "\n**********"
echo "One int, one 'int' in string constant"
echo "**********"

./$program.o <<-zzz 
int age;
char *foo = "this is not an int";
zzz

echo "\n**********"
echo "One char, one 'char' in comment"
echo "**********"

./$program.o <<-zzz 
/* this is a c style comment about my char that has a * in it */
char x;
/* this is a statement with a forward slash that isn't a comment */
int y = 14/7;
zzz
