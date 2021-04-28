#!/bin/bash

PWD=$(pwd)
PROJECT_NAME=$(cat $PWD/.project_name)

compiled_binary_name="ft_ls"
compiled_binary_path="${PROJECT_NAME}/${compiled_binary_name}"

function check_for_objects
{
	obj_files=$(find ${PROJECT_NAME} -type f -name "*.o")

	if [[ $obj_files == "" ]]; then
		echo "0"
	else
		echo "1"
	fi
}

function check_for_libraries
{
	lib_files=$(find ${PROJECT_NAME} -type f -name "*.a")

	if [[ $lib_files == "" ]]; then
		echo "0"
	else
		echo "1"
	fi
}

function check_makefile_exists
{
	if [ -f "ft_ls/Makefile" ]; then
		makefile_filepath="ft_ls/Makefile"
	elif [ -f "ft_ls/makefile" ]; then
		makefile_filepath="ft_ls/makefile"
	else
		printf "Makefile not found"
		exit 1
	fi
}

function clean_project
{
	make -C $PROJECT_NAME fclean > /dev/null 2>&1

	if [ -f $compiled_binary_path ]; then
		printf "Cleaning directory failed when processing 'fclean' rule"
		exit 1
	fi

	if [ check_for_objects == 1 ]; then
		printf "Cleaning directory failed when processing 'fclean' rule"
		exit 1
	fi
}

function check_makefile_all
{
	make_result="$(make -C $PROJECT_NAME all -j9)"

	if [[ $(echo $make_result | grep "No rule to make target 'all'") != "" ]]; then
		printf "Missing rule 'all'"
		exit 1
	fi

	if [ ! -f $compiled_binary_path ]; then
		printf "Rule 'all' should have compiled a binary named '$compiled_binary_name'"
		exit 1
	fi

	if [ $(check_for_objects) == "0" ]; then
		printf "Rule 'all' should have compiled object files"
		exit 1
	fi
	
	make_result="$(make -C $PROJECT_NAME all -j9)"

	if [ "$(echo $make_result | grep "Nothing to be done")" == "" ]; then
		printf "Running rule 'all' twice should not recompile"
		exit 1
	fi
}

function check_makefile_clean
{
	make_result="$(make -C $PROJECT_NAME clean)"

	if [[ $(echo $make_result | grep "No rule to make target 'clean'") != "" ]]; then
		printf "Missing rule 'clean'"
		exit 1
	fi


	if [ ! -f $compiled_binary_path ]; then
		printf "Rule 'clean' should not have cleaned the binary named '$compiled_binary_name'"
		exit 1
	fi

	if [ $(check_for_objects) != 0 ]; then
		printf "Rule 'clean' should have cleaned the object files"
		exit 1
	fi
}

function check_makefile_re
{
	original_binary_time=$(stat -c '%Y' ${compiled_binary_path})
	make_result="$(make -C $PROJECT_NAME re -j9)"

	if [[ $(echo $make_result | grep "No rule to make target 're'") != "" ]]; then
		printf "Missing rule 're'"
		exit 1
	fi

	if [ $(check_for_objects) == 0 ]; then
		printf "Rule 're' should have rebuilt object files"
		exit 1
	fi

	if [ ! -f $compiled_binary_path ]; then
		printf "Rule 're' should have recompiled the binary named '$compiled_binary_name'"
		exit 1
	fi

	if [ $(stat -c '%Y' ${compiled_binary_path}) == $original_binary_time ]; then
		printf "Rule 're' should have recompiled the binary named '$compiled_binary_name'"
		exit 1
	fi
}

function check_makefile_fclean
{
	make_result="$(make -C $PROJECT_NAME fclean)"


	if [[ $(echo $make_result | grep "No rule to make target 'fclean'") != "" ]]; then
		printf "Missing rule 'fclean'"
		exit 1
	fi

	if [ $(check_for_objects) == 1 ]; then
		printf "Rule 'fclean' should have cleaned object files"
		exit 1
	fi

	if [ -f $compiled_binary_path ]; then
		printf "Rule 'fclean' should have cleaned the binary named '$compiled_binary_name'"
		exit 1
	fi

	if [ $(check_for_libraries) == 1 ]; then
		printf "Rule 'fclean' should have cleaned the libraries"
		exit 1
	fi
}

function check_makefile_name
{
	make_result="$(make -C $PROJECT_NAME ${compiled_binary_name} -j9)"

	if [[ $(echo $make_result | grep "No rule to make target '${compiled_binary_name}'") != "" ]]; then
		printf "Missing rule '${compiled_binary_name}'"
		exit 1
	fi

	if [ ! -f $compiled_binary_path ]; then
		printf "Rule '${compiled_binary_name}' should have compiled a binary named '$compiled_binary_name'"
		exit 1
	fi

	if [ $(check_for_objects) == "0" ]; then
		printf "Rule '${compiled_binary_name}' should have compiled object files"
		exit 1
	fi
	
	make_result="$(make -C $PROJECT_NAME ${compiled_binary_name} -j9)"

	if [ "$(echo $make_result | grep "Nothing to be done")" == "" \
		-a "$(echo $make_result | grep "'$compiled_binary_name' is up to date")" == "" ]; then
		printf "Running rule '${compiled_binary_name}' twice should not recompile"
		exit 1
	fi
}

check_makefile_exists
clean_project
check_makefile_all
check_makefile_clean
check_makefile_re
check_makefile_fclean
check_makefile_name
exit 0
