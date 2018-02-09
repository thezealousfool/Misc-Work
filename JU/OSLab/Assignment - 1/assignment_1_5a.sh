#!/bin/bash

if [ $# -lt 1 ]
then
    printf "usage: %s <files>\n" "$0"
    exit 0
fi

for location in "$@"
do
    tmp_loc=$(realpath "$location")
    if [ -f "$tmp_loc" ]
    then
        count=`grep -o -n "This is my program" $tmp_loc | wc -l`
        printf "%s: %d\n" $tmp_loc $count
    else
        printf "%s: is not a valid file\n" "$tmp_loc"
    fi
done
