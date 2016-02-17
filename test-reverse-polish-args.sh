#!/bin/zsh

function run_commands () 
{
  echo
  echo "$1"

  eval "./reverse-polish-args.o $1"

  echo "________________________________"
}

echo "Test reverse-polish"
clang -g -Wall -Wextra -Wpedantic -lm reverse-polish-args.c -o reverse-polish-args.o || exit 1

run_commands "4 5 /"

run_commands "1 2 - 4 5 + *"

run_commands "97 10 %"

run_commands "4 0 %"

run_commands "45 @sin"

run_commands "3 @exp"

run_commands "2 4 @pow"

echo "done!"



