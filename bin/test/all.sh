#!/bin/bash

COLOR_RED='\033[91m'
COLOR_GRN='\033[92m'
COLOR_END='\033[00m'
FAILED="${COLOR_RED}FAILED${COLOR_END}"
SUCCESS="${COLOR_GRN}OK${COLOR_END}"

printf "Author\t:\t"
author=$(bash bin/test/author.sh)
author_exit_status=$?
if [ $author_exit_status != 0 ]; then
	printf "${COLOR_RED}$author${COLOR_END}"
else
	for name in $author; do
		printf "${COLOR_GRN}$name${COLOR_END} "
	done
fi

printf "\nNorm\t:\t"
norm=$(bash bin/test/norm.sh > /dev/null 2>&1; echo $?)
if [ $norm = "0" ]; then
	printf "$SUCCESS"
else
	printf "$FAILED"
fi

printf "\nBehavior\t:\t"
behavior=$(bash bin/test/behavior.sh; echo $?)
if [ $behavior = "0" ]; then
	printf "$SUCCESS"
else
	printf "$FAILED"
fi

printf "\nLeaks\t:\t"
leaks=$(bash bin/test/leaks.sh; echo $?)
if [ $leaks = "0" ]; then
	printf "$SUCCESS"
else
	printf "$FAILED"
fi

printf "\n"
