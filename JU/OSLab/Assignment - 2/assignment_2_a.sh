#!/bin/bash

gcc assignment_2_a_caller.c -o assignment_2_a_caller
gcc assignment_2_a_receiver.c -o assignment_2_a_receiver
x-terminal-emulator -e ./assignment_2_a_caller
x-terminal-emulator -e ./assignment_2_a_receiver
