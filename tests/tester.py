#!/usr/bin/env python3.8

import os
import sys
import subprocess as sb

from test_suites.test_l_flag import run_test_l_flag
from test_suites.test_r_flag import run_test_r_flag
from testing_utils.test_from_cli import test_from_cli


def run_test_suites():
    run_test_l_flag()
    run_test_r_flag()


if __name__ == '__main__':
    ls_path = sb.check_output(["which", "ls"]).decode("utf-8").replace("\n", "")
    ft_ls_path = os.path.join(os.path.dirname(__file__), "../ft_ls/ft_ls")
    if len(sys.argv) > 1:
        test_from_cli(sys.argv[1:])
    else:
        run_test_suites()
