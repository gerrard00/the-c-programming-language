#! /bin/zsh

set -e

clang -g -Wall -Wextra -Wpedantic fopen-with-flushbuf.c -o fopen-with-flushbuf.o


echo "test flushbuf\n\n"

echo "\n\n*****************************"
echo "type-ranges.c"
echo "*****************************"

file1=type-ranges.c
file2=delete.c

time ./fopen-with-flushbuf.o $file1 $file2
echo "*****************************"
stat -c "input:  $file1 %s" $file1
stat -c "output: $file2 %s" $file2
diff $file1 $file2
echo "*****************************"

echo "\n\n*****************************"
echo "random file"
echo "*****************************"

file1=$(mktemp /tmp/file1.XXXXXX)
echo "begin|" > $file1
base64 /dev/urandom | head -c 33000 >> $file1
echo "|end" >> $file1
file2=$(mktemp /tmp/file2.XXXXXX)
time ./fopen-with-flushbuf.o $file1 $file2
echo "*****************************"
stat -c "input:  $file1 %s" $file1
stat -c "output: $file2 %s" $file2
diff $file1 $file2
echo "*****************************"
