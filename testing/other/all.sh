#!/bin/bash

TEST_SCRIPTS_DIR="testing/other"
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
author=$(bash ${TEST_SCRIPTS_DIR}/author.sh)
author_exit_status=$?
if [ $author_exit_status != 0 ]; then
	print_failure "$author"
else
	for name in $author; do
		print_success "$name"
	done
fi

printf "\nNorm\t\t:\t"
norm=$(bash ${TEST_SCRIPTS_DIR}/norm.sh)
norm_exit_status=$?
if [ $norm_exit_status != 0 ]; then
	print_failure "$norm"
else
	print_success "$norm"
fi

printf "\nMakefile\t:\t"
makefile=$(bash ${TEST_SCRIPTS_DIR}/makefile.sh)
makefile_exit_status=$?
if [ $makefile_exit_status != 0 ]; then
	print_failure "$makefile"
else
	print_success "$SUCCESS"
fi

printf "\nBehavior\t:\t"
behavior=$(bash ${TEST_SCRIPTS_DIR}/behavior.sh; echo $?)
if [ $behavior = "0" ]; then
	print_success "$SUCCESS"
else
	print_failure "$FAILED"
fi

printf "\nOverflows\t:\t"
overflows=$(bash ${TEST_SCRIPTS_DIR}/overflows.sh; echo $?)
if [ $overflows = "0" ]; then
	print_success "$SUCCESS"
else
	print_failure "$FAILED"
fi

printf "\nLeaks\t\t:\t"
leaks=$(bash ${TEST_SCRIPTS_DIR}/leaks.sh; echo $?)
if [ $leaks = "0" ]; then
	print_success "$SUCCESS"
else
	print_failure "$FAILED"
fi

printf "\nMallocs\t\t:\t"
malloc_protections=$(bash ${TEST_SCRIPTS_DIR}/malloc.sh; echo $?)
if [ $malloc_protections = "0" ]; then
	print_success "$SUCCESS"
elif [ $malloc_protections = "1" ]; then
	print_failure "Found unprotected call(s)"
else
	print_failure "Unknown Error"
fi

printf "\n"
