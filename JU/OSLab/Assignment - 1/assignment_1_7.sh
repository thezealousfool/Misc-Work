#!/bin/bash

if [ $# -lt 1 ]
then
    printf "usage: %s <numbers>\n" "$0"
    exit 0
fi

isPrime() {
    i=2
    while [ $i -lt $1 ]
    do
        if [ $(( $1 % $i )) -eq 0 ]
        then
            printf "%5d: Not prime\n" $1
            return
        fi
        i=$(( $i+1 ))
    done
    printf "%5d: Prime\n" $1
}

for number in "$@"
do
    isPrime $number
done
