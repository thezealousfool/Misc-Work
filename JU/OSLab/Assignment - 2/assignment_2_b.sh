#!/bin/bash

if [ $# -lt 1 ]
then
  printf "usage: %s <no of receivers>\n" "$0"
  exit 0
fi

gcc assignment_2_a_caller.c -o assignment_2_a_caller
gcc assignment_2_a_receiver.c -o assignment_2_a_receiver

x-terminal-emulator -e ./assignment_2_a_caller $1
for i in $(seq 1 $1)
do
  x-terminal-emulator -e ./assignment_2_a_receiver $1
done
