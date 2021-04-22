#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

docker run -it --rm --user `id -u` --name ${PROJECT_NAME}-test \
	-v ${PWD}:/workspace \
	--net host \
	-w /workspace \
	${PROJECT_NAME}-dev /bin/bash bin/test/all.sh
