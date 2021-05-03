#!/bin/bash

files=$(find ft_ls -type f \( -name \*.c -o -name \*.h \))
norminette $files
