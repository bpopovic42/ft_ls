#!/bin/bash

make DEBUG="-g -fsanitize=address -fsanitize=leak" re -j9 -C ft_ls > /dev/null 2>&1

leaks=$(testing/tester/run.py -e "-p" | grep "leaked in" | wc -l)

if [ $leaks = "0" ]; then
	exit 0
else
	exit 1
fi
