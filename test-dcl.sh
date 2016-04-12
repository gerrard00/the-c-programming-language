#! /bin/zsh

program=dcl

clear
tmux clear-history

echo "Test $program\n"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c dcl-common.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "default"
echo "**********"

./$program.o <<-zzz 
char (*x)()
zzz

echo "\n**********"
echo "harder"
echo "**********"

./$program.o <<-zzz 
char (*(*x())[])()
int *test()
char *(*(*foo())[])()
zzz

echo "\n**********"
echo "first not ended"
echo "**********"

./$program.o <<-zzz 
char (*(*first())[])(
int *second()
zzz

echo "\n**********"
echo "second bad"
echo "**********"

./$program.o <<-zzz 
int first[]
char ()**second
bool (*third[])()
zzz

echo "\n**********"
echo "function argumemts"
echo "**********"

./$program.o <<-zzz 
int bar(int x, char y)
zzz

echo "\n**********"
echo "function arguments array"
echo "**********"

./$program.o <<-zzz 
bool unique(char characters[], int size)
zzz

echo "\n**********"
echo "function with args returning pointer"
echo "**********"

./$program.o <<-zzz 
int *bang(int x, int y)
zzz
