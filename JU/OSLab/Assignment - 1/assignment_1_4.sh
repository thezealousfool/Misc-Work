#!/bin/bash

if [ $# -lt 1 ]
then
	printf "usage: %s <5-digit-numbers>\n" "$0"
	exit 0
fi

for val in $@
do
	if [ ${#val} -ne 5 ] || ! [[ $val =~ ^[0-9]+$ ]]
	then
		printf "%s is not a 5 digit number\n" "$val"
	else
		echo $val|rev
	fi
done
