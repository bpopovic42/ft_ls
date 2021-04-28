#!/bin/bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

make DEBUG="-g -fsanitize=leak" re -j9 -C ${PROJECT_NAME} > /dev/null 2>&1

leaks=$(testing/tester/run.py -e "-p" | grep "leaked in" | wc -l)

if [ $leaks = "0" ]; then
	exit 0
else
	exit 1
fi
