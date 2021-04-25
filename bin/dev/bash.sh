#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)
TEST_DIR="tests"

docker run --rm -ti --user `id -u` --name ${PROJECT_NAME}-bash \
	-v ${PWD}/${PROJECT_NAME}:/workspace/${PROJECT_NAME} \
	-v ${PWD}/${TEST_DIR}:/workspace/${TEST_DIR} \
	-v ${PWD}/bin:/workspace/bin \
	-v ${PWD}/testing:/workspace/testing \
	--net host \
	-w /workspace \
	${PROJECT_NAME}-dev /bin/zsh
