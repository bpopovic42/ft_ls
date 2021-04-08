#!/usr/bin/env python3.8

import sys

from test_suites.test_bonus_non_printable import run_test_bonus_non_printable
from test_suites.test_sys_dev import run_test_sys_dev
from test_suites.test_sys_usr_bin import run_test_sys_usr_bin
from test_suites.test_flags_mix import run_test_flags_mix
from test_suites.test_special_bits_dir import run_test_special_bits_dir
from test_suites.test_special_bits import run_test_special_bits
from test_suites.test_multiple_files import run_test_multiple_files
from test_suites.test_symlink import run_test_symlink
from test_suites.test_aR_flag import run_test_aR_flag
from test_suites.test_alR_flag import run_test_alR_flag
from test_suites.test_hyphen import run_test_hyphen
from test_suites.test_hyphen_harder import run_test_hyphen_harder
from test_suites.test_perms import run_test_perms
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
    run_test_aR_flag()
    run_test_alR_flag()
    run_test_perms()
    run_test_hyphen()
    run_test_hyphen_harder()
    run_test_symlink()
    run_test_multiple_files()
    run_test_special_bits()
    run_test_special_bits_dir()
    run_test_flags_mix()
    run_test_sys_usr_bin()
    run_test_sys_dev()
    #run_test_bonus_non_printable()
    print("\nSee '{}/[TEST_NAME]' for failed tests output\n".format(SANDBOXES_DIR))


if __name__ == '__main__':
    clean_existing_tests()
    if len(sys.argv) > 1:
        test_from_cli(" ".join(sys.argv[1:]))
    else:
        run_test_suites()
