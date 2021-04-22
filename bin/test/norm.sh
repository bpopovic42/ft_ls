#!/bin/bash

norm_errors=$(norminette ft_ls/**/*[.c,.h] | grep Error | wc -l)

echo ${norm_errors}

if [ $norm_errors = "0" ]; then
	exit 0
else
	exit 1
fi
