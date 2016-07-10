#! /bin/zsh

program=compare-files
clear
tmux clear-history

echo "^^^^^^^Test $pr^^^^^^^"
gcc -g -Wall -Wextra -Wpedantic -Werror $program.c -o $program.o

if [[ $? -ne 0 ]]; then
  exit
fi

file1=$(mktemp /tmp/file1.XXXXXX)
file2=$(mktemp /tmp/file2.XXXXXX)

echo "\n**********"
echo "default"
echo "**********"

echo "this\nis\ngerrard\nlindsay" > $file1
echo "this\nis\nanthony\nlindsay" > $file2
# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./$program.o $file1 $file2

echo "\n**********"
echo "identical"
echo "**********"

echo "this\nis\ngerrard\nlindsay" > $file1
echo "this\nis\ngerrard\nlindsay" > $file2
# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./$program.o $file1 $file2

echo "\n**********"
echo "first shorter"
echo "**********"

echo "this\nis\na\nfile" > $file1
echo "this\nis\na\nfile\nwith more stuff" > $file2
# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./$program.o $file1 $file2

echo "\n**********"
echo "second shorter"
echo "**********"

echo "this\nis\na\nfile\nwith a lot of stuff" > $file1
echo "this\nis\na\nfile" > $file2
# valgrind --leak-check=full --show-leak-kinds=all ./$program.o <<-zzz
./$program.o $file1 $file2
