#!/bin/bash

COLOR_RED='\033[91m'
COLOR_GRN='\033[92m'
COLOR_END='\033[00m'
FAILED="FAILED"
SUCCESS="OK"

print_success()
{
	message="$1"
	printf "${COLOR_GRN}$message${COLOR_END}"
}

print_failure()
{
	message="$1"
	printf "${COLOR_RED}$message${COLOR_END}"
}

printf "Author\t\t:\t"
author=$(bash bin/test/author.sh)
author_exit_status=$?
if [ $author_exit_status != 0 ]; then
	print_failure "$author"
else
	for name in $author; do
		print_success "$name"
	done
fi

printf "\nNorm\t\t:\t"
norm=$(bash bin/test/norm.sh)
norm_exit_status=$?
if [ $norm_exit_status != 0 ]; then
	print_failure "$norm"
else
	print_success "$norm"
fi

printf "\nMakefile\t:\t"
makefile=$(bash bin/test/makefile.sh)
makefile_exit_status=$?
if [ $makefile_exit_status != 0 ]; then
	print_failure "$makefile"
else
	print_success "$SUCCESS"
fi

printf "\nBehavior\t:\t"
behavior=$(bash bin/test/behavior.sh; echo $?)
if [ $behavior = "0" ]; then
	print_success "$SUCCESS"
else
	print_failure "$FAILED"
fi

printf "\nLeaks\t\t:\t"
leaks=$(bash bin/test/leaks.sh; echo $?)
if [ $leaks = "0" ]; then
	print_success "$SUCCESS"
else
	print_failure "$FAILED"
fi

printf "\n"
