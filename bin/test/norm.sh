#!/usr/bin/env bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)
TEST_DIR="testing"

docker run --rm -ti --user `id -u` --name ${PROJECT_NAME}-test \
	-v ${PWD}/${PROJECT_NAME}:/workspace/${PROJECT_NAME} \
	-v ${PWD}/${TEST_DIR}:/workspace/${TEST_DIR} \
	--net host \
	-w /workspace \
	${PROJECT_NAME}-dev bash testing/other/norm_output.sh
