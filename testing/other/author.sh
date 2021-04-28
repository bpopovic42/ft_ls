#!/bin/bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

if test -f "${PROJECT_NAME}/author" -a -f "${PROJECT_NAME}/auteur"; then
	printf "Multiple author files found\n"
	exit 1
elif test -f "${PROJECT_NAME}/author"; then
	FILE="${PROJECT_NAME}/author"
elif test -f "${PROJECT_NAME}/auteur"; then
	FILE="${PROJECT_NAME}/auteur"
else
	printf "File not found\n"
	exit 1
fi

if [ ! -s $FILE ]; then
	printf "File is empty\n"
	exit 1
fi

if [ "$(tail -c 1 $FILE)" != "" ]; then
	printf "No newline at EOF\n"
	exit 1
fi

while read -r line; do
	echo $line
done < $FILE

exit 0
