#! /bin/zsh

program=strindex-files
clang -g -Wall -Wextra -Wpedantic $program.c -o $program.o

echo '\n***************'
echo "stdin"
echo '***************\n'

./$program.o ould <<-zzz
no way
could
not a match bro
this could be could really be
this won't be
this would be
zzz

echo '\n***************'
echo "input file doesn't exist"
echo '***************\n'

./$program.o ould file_that_aint_there

echo '\n***************'
echo "two input files with, one without"
echo '***************\n'


file1=$(mktemp /tmp/file1.XXXXXX)
file2=$(mktemp /tmp/file2.XXXXXX)
file3=$(mktemp /tmp/file3.XXXXXX)

cat << EOF > $file1
this is a bang
a boom
and a bust
with a bang at the end
EOF

# no matches
cat << EOF > $file2
in the town
where I was born
lived a man
who sailed the seas
EOF

cat << EOF > $file3
this is going to
go bang
EOF
./$program.o bang $file1 $file2 $file3

echo "done!"
