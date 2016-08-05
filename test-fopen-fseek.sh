#! /bin/zsh

set -e

clang -g -Wall -Wextra -Wpedantic fopen-with-fseek.c -o fopen-with-fseek.o


echo "test flushbuf"

echo "\n\n*****************************"
echo "type-ranges.c: at 2nd char (index 1) skip 6 chars from current"
echo "in current buffer"
echo "changes #include to #i"
echo "*****************************"

file1=type-ranges.c
file2=delete.c

time ./fopen-with-fseek.o $file1 $file2 1 6 1
echo "*****************************"
stat -c "input:  $file1 %s" $file1
stat -c "output: $file2 %s" $file2
diff $file1 $file2 || true
echo "*****************************"

echo "\n\n*****************************"
echo "random file, skip 8200 chars at 6th char"
echo "past current buffer"
echo "output just begin||end"
echo "len 10 + 1 (newline) = 11"
echo "*****************************"

file1=$(mktemp /tmp/file1.XXXXXX)
echo -n "begin|" > $file1
base64 /dev/urandom | head -c 8200 >> $file1
echo "|end" >> $file1
file2=$(mktemp /tmp/file2.XXXXXX)

time ./fopen-with-fseek.o $file1 $file2 5 8200 1
echo "*****************************"
stat -c "input:  $file1 %s" $file1
stat -c "output: $file2 %s" $file2
cat $file2
echo "*****************************"

echo "\n\n*****************************"
echo "random file, at char 3 skip 1000 from origin"
echo "in current buffer"
echo "output just <3 chars>|middle|<1000 chars>"
echo "file length should be 3 + 1000 = 1003"
echo "*****************************"

file1=$(mktemp /tmp/file1.XXXXXX)
base64 /dev/urandom | head -c 1000 >> $file1
echo -n "|begin|" >> $file1
# subtract 7 for begin and 5 for end
base64 /dev/urandom | head -c 988 >> $file1
echo -n "|end|" >> $file1
file2=$(mktemp /tmp/file2.XXXXXX)

time ./fopen-with-fseek.o $file1 $file2 2 1000 0
echo "*****************************"
stat -c "input:  $file1 %s" $file1
stat -c "output: $file2 %s" $file2
echo
head -1 $file2
echo "*****************************"

echo "\n\n*****************************"
echo "random file, read 3, then skip to 18000 from origin"
echo "past current buffer"
echo "output just <3 chars>|middle|<1000 chars>"
echo "file length should be 3 + 8 + 1000 = 1011"
echo "*****************************"

file1=$(mktemp /tmp/file1.XXXXXX)
base64 /dev/urandom | head -c 18000 >> $file1
echo -n "|middle|" >> $file1
base64 /dev/urandom | head -c 1000 >> $file1
file2=$(mktemp /tmp/file2.XXXXXX)
./fopen-with-fseek.o $file1 $file2 2 18000 0
echo "*****************************"
stat -c "input:  $file1 %s" $file1
stat -c "output: $file2 %s" $file2
echo "*****************************"
echo "*****************************"
head -2 $file2
echo "*****************************"
