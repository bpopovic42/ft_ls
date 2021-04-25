#/bin/bash

failed_tests=$(testing/tester/run.py > /dev/null 2>&1; echo $?)

if [ $failed_tests = "0" ]; then
	exit 0
else
	exit 1
fi
