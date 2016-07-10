#!/bin/zsh

function run_commands ()
{
  echo
  echo "$1"

  ./reverse-polish.o <<< "$1"

  echo "________________________________"
}

echo "Test reverse-polish"
clang -g -Wall -Wextra -Wpedantic -lm reverse-polish.c -o reverse-polish.o || exit 1

run_commands "4 5 /"

run_commands "1 2 - 4 5 + *"

run_commands "97 10 %"

run_commands "4 0 %"

run_commands "45 @sin"

run_commands "3 @exp"

run_commands "2 4 @pow"

echo "\nvariables"
run_commands '3 A 2 B
$B $A /
c
$B $A @pow'

echo "\nlast variable"
run_commands '4 3 *
$! 6 +'

echo "\nlast variable set fail"
run_commands '4 !'

echo "done!"



