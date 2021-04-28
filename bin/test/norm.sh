#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)
TEST_DIR="testing"

docker run --rm -ti --user `id -u` --name ${PROJECT_NAME}-test \
	-v ${PWD}/${PROJECT_NAME}:/workspace/${PROJECT_NAME} \
	--net host \
	-w /workspace \
	${PROJECT_NAME}-dev norminette ${PROJECT_NAME}/**/*[.c,.h]
