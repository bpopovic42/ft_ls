#!/usr/bin/env bash

# TODO: Use python for running those tests ?
# Quick tests on branches (only one compilation ?) and complete tests when
# merging to master ?

WARNING_STATE=0
ERROR_STATE=0

# Temporary method
# Check norm, only print results if at least one error was found
# TODO: Norm program should be modified to return number of reported errors
# that return value should in turn be used here instead of current method
norm42_output=$(find /workspace -type f -name "*.c" -exec norminette {} +)
if [[ $norm42_output == *"Error"* || $norm42_output == *"Warning"* ]]; then
  echo "$norm42_output"
  WARNING_STATE=$((WARNING_STATE+1))
fi

# Makefile checker (run only if makefile was modified ?)
# run makefile -> check compilation success
# run makefile again -> check no recompilation or relink
# run clean, fclean and re -> check if working as intended

# Malloc checker
# Ideally re-implement existing malloc checker

