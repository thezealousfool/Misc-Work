#!/bin/bash

if [ $# -lt 1 ]
then
	printf "usage: %s <directories>\n" "$0"
	exit 0
fi

for location in "$@"
do
	tmp_loc=$(realpath "$location")
	if [ -d "$tmp_loc" ]
	then
		chmod 660 "$tmp_loc";
	else
		printf "%s: No such directory\n" "$tmp_loc"
	fi
done
