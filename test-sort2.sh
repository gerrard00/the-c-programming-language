#! /bin/zsh

program=sort2

echo "Test $program\n"
clang -g -Wall -Wextra -Wpedantic $program.c -o $program.o


if [[ $? -ne 0 ]]; then
  exit
fi

echo "\n**********"
echo "default"
echo "**********"

./$program.o <<-zzz 
1
300
25
4
495
zzz

echo "\n**********"
echo "numeric"
echo "**********"

./$program.o -n <<-zzz 
1
300
25
4
495
zzz

echo "\n**********"
echo "default reverse"
echo "**********"

./$program.o -r <<-zzz 
1
300
25
4
495
zzz

echo "\n**********"
echo "numeric reverse"
echo "**********"

./$program.o -r -n <<-zzz 
1
300
25
4
495
zzz

