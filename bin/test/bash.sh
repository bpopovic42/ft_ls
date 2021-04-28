#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)
TEST_DIR="testing"

docker run --rm -ti --user `id -u` --name ${PROJECT_NAME}-test \
	-v ${PWD}/${PROJECT_NAME}:/workspace/${PROJECT_NAME} \
	-v ${PWD}/.project_name:/workspace/.project_name \
	-v ${PWD}/${TEST_DIR}:/workspace/${TEST_DIR} \
	-v ${PWD}/bin:/workspace/bin \
	--net host \
	-w /workspace \
	${PROJECT_NAME}-dev /bin/zsh
