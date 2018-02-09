#!/bin/bash

if [ $# -lt 1 ]
then
    printf "usage: %s <files>\n" "$0"
    exit 0
fi

gtotal=0
for location in "$@"
do
    tmp_loc=$(realpath "$location")
    if [ -f "$tmp_loc" ]
    then
        count=`grep -o -n "This is my program" $tmp_loc | wc -l`
        gtotal=$(((gtotal)+(count)))
        sed -i 's/This is my program/This is copied program/g' $tmp_loc
    else
        printf "%s: is not a valid file\n" $tmp_loc
    fi
done
printf "Total no of occurences: %d\n" $gtotal
