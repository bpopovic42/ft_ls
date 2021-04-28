#!/bin/bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

make DEBUG="-g -fsanitize=address" re -j9 -C ${PROJECT_NAME} > /dev/null 2>&1

overflows=$(testing/tester/run.py -e "-p" | grep "overflow on address" | wc -l)

if [ $overflows = "0" ]; then
	exit 0
else
	exit 1
fi
