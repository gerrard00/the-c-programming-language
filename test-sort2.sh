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
echo "numeric and reverse"
echo "**********"

./$program.o -rn <<-zzz 
1
300
25
4
495
zzz

echo "\n**********"
echo "case sensitive"
echo "**********"

./$program.o <<-zzz 
aaaaaaaaaddd
aaa
bbb
AAA
BBB
ccc
zzz

echo "\n**********"
echo "case insensitive"
echo "**********"

./$program.o -f <<-zzz 
aaaaaaaaaddd
aaa
bbb
AAA
BBB
ccc
zzz

echo "\n**********"
echo "case insensitive reverse"
echo "**********"

./$program.o -fr <<-zzz 
aaaaaaaaaddd
aaa
bbb
AAA
BBB
ccc
zzz

echo "\n**********"
echo "without directory"
echo "**********"

./$program.o <<-zzz 
AAABBBCCC
AAA.ccc.ddd
aaa/bbb/ccc
aaa/ddd/eee
aaabbbccc
AAA/BBB/CCC
AAA/DDD/EEE
BBB/CCC/DDD
zzz

echo "\n**********"
echo "numeric and directory fail"
echo "**********"

./$program.o -nd <<-zzz 
zzz
echo "\n**********"
echo "case sensitive directory"
echo "**********"

./$program.o -d <<-zzz 
AAABBBCCC
AAA.ccc.ddd
aaa/bbb/ccc
aaa/ddd/eee
aaabbbccc
AAA/BBB/CCC
AAA/DDD/EEE
BBB/CCC/DDD
zzz

echo "\n**********"
echo "case insensitive directory"
echo "**********"

./$program.o -fd <<-zzz 
AAABBBCCC
AAA.ccc.ddd
aaa/bbb/ccc
aaa/ddd/eee
aaabbbccc
AAA/BBB/CCC
AAA/DDD/EEE
BBB/CCC/DDD
zzz

echo "\n**********"
echo "case insensitive directory reverse"
echo "**********"

./$program.o -fdr <<-zzz 
AAABBBCCC
AAA.ccc.ddd
aaa/bbb/ccc
aaa/ddd/eee
aaabbbccc
AAA/BBB/CCC
AAA/DDD/EEE
BBB/CCC/DDD
zzz
