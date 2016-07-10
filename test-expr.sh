#!/bin/zsh

function run_commands () 
{
  echo
  echo "$1"

  eval "./expr.o $1"

  echo "________________________________"
}

echo "Test expr"
clang -g -Wall -Wextra -Wpedantic -lm expr.c -o expr.o || exit 1

run_commands "4 5 /"

run_commands "1 2 - 4 5 + *"

run_commands "97 10 %"

run_commands "4 0 %"

run_commands "45 @sin"

run_commands "3 @exp"

run_commands "2 4 @pow"

echo "done!"



