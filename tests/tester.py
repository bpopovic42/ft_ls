#!/usr/bin/env python3.8

import os
import sys
import subprocess as sb

from test_suites.test_simple import run_test_simple
from test_suites.test_R_flag import run_test_R_flag
from test_suites.test_multiple_dirs import run_test_multiple_dirs
from test_suites.test_a_flag import run_test_a_flag
from test_suites.test_r_flag import run_test_r_flag
from test_suites.test_rR_flag import run_test_rR_flag
from test_suites.test_l_flag import run_test_l_flag
from test_suites.test_sorting import run_test_sorting
from test_suites.test_t_flag import run_test_t_flag
from test_suites.test_tR_flag import run_tR_flag
from test_suites.test_error_handling import run_test_error_handling
from testing_utils.globals import SANDBOXES_DIR
from testing_utils.test_from_cli import test_from_cli

from testing_utils.utils import clean_existing_tests


def run_test_suites():
    run_test_simple()
    run_test_R_flag()
    run_test_sorting()
    run_test_multiple_dirs()
    run_test_a_flag()
    run_test_rR_flag()
    run_test_r_flag()
    run_test_t_flag()
    run_tR_flag()
    run_test_l_flag()
    run_test_error_handling()
    print("\nSee '{}/[TEST_NAME]' for failed tests output\n".format(SANDBOXES_DIR))


if __name__ == '__main__':
    clean_existing_tests()
    if len(sys.argv) > 1:
        test_from_cli(" ".join(sys.argv[1:]))
    else:
        run_test_suites()
