#! /bin/zsh

program=dcl

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
char (*(*x())[])()
zzz
# ./$program.o <<-zzz 
# char (*(*x())[])()
# int *test()
# char *((*foo())[])()
# zzz

# echo "\n**********"
# echo "first not ended"
# echo "**********"

# ./$program.o <<-zzz 
# char (*(*first())[])(
# int *second()
# zzz

# echo "\n**********"
# echo "first bad different"
# echo "**********"

# ./$program.o <<-zzz 
# int first[]
# char ()**second
# bool (*third[])()
# zzz

# echo "\n**********"
# echo "function argumemts"
# echo "**********"

# ./$program.o <<-zzz 
# int bar(int x, char y)
# zzz

# echo "\n**********"
# echo "function no argumemts"
# echo "**********"

# ./$program.o <<-zzz 
# int baz()
# zzz
