#!/bin/zsh

function run_commands () 
{
  echo
  echo "$1"

  ./getfloat.o <<< "$1"

  echo "________________________________"
}

echo "Test getfloat"
clang -g -Wall -Wextra -Wpedantic -lm getfloat.c -o getfloat.o || exit 1

run_commands "4.1"
run_commands "-10.2"
run_commands "4.1 5.2"
run_commands "3.14 -10.2"
run_commands "3.1415 +10"
run_commands "gerrard"
run_commands "3 -gerrard 6.0"
run_commands "8.01 -gerrard"

echo "done!"



