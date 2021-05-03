#!/bin/bash

files=$(find ft_ls -type f \( -name \*.c -o -name \*.h \))
norm_output=$(norminette $files)
norm_errors=$(echo "$norm_output" | grep Error)
norm_warnings=$(echo "$norm_output" | grep Warning)

if [ "$norm_errors" == "" -a "$norm_warnings" == "" ]; then
	printf "All files passed the tests"
	exit 0
else
	(( total_errors = $(echo "$norm_errors" | wc -l) + $(echo $norm_warnings | wc -l) ))
	printf "${total_errors} error(s) or warning(s)"
	exit 1
fi
