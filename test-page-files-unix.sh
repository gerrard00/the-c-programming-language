#! /bin/zsh

set -e

program=page-files-unix
clang -g -Wall -Wextra -Wpedantic $program.c -o $program.o

echo '\n***************'
echo "stdin, 2 pages"
echo '***************\n'

./$program.o <<-zzz
0000000000
1111111111
2222222222
3333333333
4444444444
5555555555
6666666666
7777777777
8888888888
zzz

echo '\n***************'
echo "input file doesn't exist"
echo '***************\n'

./$program.o file_that_aint_there || true

echo '\n***************'
echo "3 files"
echo '***************\n'


file1=$(mktemp /tmp/file1.XXXXXX)
file2=$(mktemp /tmp/file2.XXXXXX)
file3=$(mktemp /tmp/file3.XXXXXX)

cat << EOF > $file1
this
is
one
page
long
EOF

# no matches
cat << EOF > $file2
0000000000
1111111111
2222222222
3333333333
4444444444
5555555555
6666666666
7777777777
8888888888
9999999999
aaaaaaaaaa
EOF

cat << EOF > $file3
this
is
short
EOF
./$program.o $file1 $file2 $file3
echo "\ndone! done! done!\n"
