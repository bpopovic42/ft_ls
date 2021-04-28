#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)
TEST_DIR="testing"


make DEBUG="-g" re -j9 -C ft_ls &> /dev/null

docker run --rm -i --user `id -u` --name ${PROJECT_NAME}-test \
	-v ${PWD}/${PROJECT_NAME}:/workspace/${PROJECT_NAME} \
	-v ${PWD}/${TEST_DIR}:/workspace/${TEST_DIR} \
	-e TERM=xterm \
	--net host \
	-w /workspace \
	${PROJECT_NAME}-dev python3.8 ${TEST_DIR}/other/malloc_crasher.py -a "-alrRt /workspace" -p ${PROJECT_NAME}/ft_ls
