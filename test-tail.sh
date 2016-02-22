#! /bin/zsh

program=tail

echo "Test $program\n"
clang -g -Wall -Wextra -Wpedantic $program.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "4/6"
echo "**********"

./$program.o -4 <<-zzz 
this
is
a
series
of 
lines
zzz

echo "\n**********"
echo "?/6"
echo "**********"

./$program.o <<-zzz 
this
is
a
series
of 
lines
zzz

echo "\n**********"
echo "10/6"
echo "**********"

./$program.o -10 <<-zzz 
this
is
a
series
of 
lines
zzz
