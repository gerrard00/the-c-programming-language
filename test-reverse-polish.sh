#! /bin/zsh

echo "Test reverse-polish\n"
clang -g -Wall -Wextra -Wpedantic -lm reverse-polish.c -o reverse-polish.o &&./reverse-polish.o || exit 1

mkfifo mypipe
./reverse-polish.o < mypipe &

# echo "1 2 - 4 5 + *"
# echo "1 2 - 4 5 + *" > mypipe

# echo
# echo "1 2 *"
# echo "1 2 *" > mypipe

# echo
# echo "45 @sin"
# echo "45 @sin" > mypipe

# echo
# echo "3 @exp"
# echo "3 @exp" > mypipe

# echo
# echo "2 3 @pow"
# echo "2 3 @pow" > mypipe

# echo "variables"
# echo "4 a" > mypipe
# echo "p" > mypipe
# echo "3 b" > mypipe
# echo "c" > mypipe
# echo '$b $a @pow' > mypipe

echo 'last variable'
echo '4 3 *' > mypipe
echo '$! 6 +' > mypipe

echo 'last variable set fail'
echo '4 !' > mypipe

rm mypipe

echo
echo "done!"
