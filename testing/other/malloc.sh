#!/bin/bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

make DEBUG="-g" re -j9 -C ${PROJECT_NAME} > /dev/null 2>&1

malloc_protection=$(python3.8 testing/other/malloc_crasher.py -a "-alrRt ${PWD}" ${PROJECT_NAME}/ft_ls; echo $?)

if [ $malloc_protection = "0" ]; then
	exit 0
elif [ $malloc_protection = "-1" ]; then
	exit -1
else
	exit 1
fi
