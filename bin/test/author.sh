#!/bin/bash

if test -f "ft_ls/author" -a -f "ft_ls/auteur"; then
	printf "Multiple author files found\n"
	exit 1
elif test -f "ft_ls/author"; then
	FILE="ft_ls/author"
elif test -f "ft_ls/auteur"; then
	FILE="ft_ls/auteur"
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
