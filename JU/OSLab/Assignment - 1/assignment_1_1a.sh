#!/bin/bash

if [ $# -lt 1 ]
then
	printf "usage: %s <directories>\n" "$0"
	exit 0
fi


count_files_folders() {
	tmp_loc=$(realpath "$1")
	if [ -d "$tmp_loc" ]
	then
		path=$(realpath --relative-to="$2" "$tmp_loc")
		filecount=$(find "$tmp_loc" -maxdepth 1 -type f | wc -l)
		printf "Files: %d   %s\n" "$filecount" "$path"
	else
		printf "%s: No such directory\n" "$tmp_loc"
	fi
}

for location in "$@"
do
	count_files_folders "$location" "$location"
done
