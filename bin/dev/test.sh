#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

docker run --rm -ti --user `id -u` --name ${PROJECT_NAME}-test \
	-v ${PWD}/${PROJECT_NAME}:/workspace \
	-v ${PWD}/testing:/testing \
	--net host \
	-w /workspace \
	${PROJECT_NAME}-dev /bin/bash /testing/test.sh
