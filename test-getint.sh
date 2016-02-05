#!/bin/zsh

function run_commands () 
{
  echo
  echo "$1"

  ./getint.o <<< "$1"

  echo "________________________________"
}

echo "Test getint"
clang -g -Wall -Wextra -Wpedantic -lm getint.c -o getint.o || exit 1

run_commands "4 5"
run_commands "3 -10"
run_commands "3 +10"
run_commands "gerrard"
run_commands "3 -gerrard 6"
run_commands "8 -gerrard"

echo "done!"



