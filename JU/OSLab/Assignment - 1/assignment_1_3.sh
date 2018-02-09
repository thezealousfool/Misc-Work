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
		printf "Lines: %5d   %s\n" `cat "$tmp_loc" | wc -l` "$tmp_loc"
	else
		printf "%s: No such file\n" "$tmp_loc"
	fi
done
