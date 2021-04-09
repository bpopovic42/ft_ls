from test_suites.test_bonus_non_printable import get_tests_bonus_non_printable
from test_suites.test_sys_var_run import get_tests_sys_var_run
from test_suites.test_sys_etc import get_tests_sys_etc
from test_suites.test_sys_dev import get_tests_sys_dev
from test_suites.test_sys_usr_bin import get_tests_sys_usr_bin
from test_suites.test_flags_mix import get_tests_flags_mix
from test_suites.test_special_bits_dir import get_tests_special_bits_dir
from test_suites.test_special_bits import get_tests_special_bits
from test_suites.test_multiple_files import get_tests_multiple_files
from test_suites.test_symlink import get_tests_symlink
from test_suites.test_aR_flag import get_tests_aR_flag
from test_suites.test_alR_flag import get_tests_alR_flag
from test_suites.test_hyphen import get_tests_hyphen
from test_suites.test_hyphen_harder import get_tests_hyphen_harder
from test_suites.test_perms import get_tests_perms
from test_suites.test_simple import get_tests_simple
from test_suites.test_R_flag import get_tests_R_flag
from test_suites.test_multiple_dirs import get_tests_multiple_dirs
from test_suites.test_a_flag import get_tests_a_flag
from test_suites.test_r_flag import get_tests_r_flag
from test_suites.test_rR_flag import get_tests_rR_flag
from test_suites.test_l_flag import get_tests_l_flag
from test_suites.test_sorting import get_tests_sorting
from test_suites.test_t_flag import get_tests_t_flag
from test_suites.test_tR_flag import get_tests_tR_flag
from test_suites.test_error_handling import get_tests_error_handling
from test_suites.test_parsing import get_tests_parsing


def get_all_tests():
    tests = []
    tests += get_tests_simple()
    tests += get_tests_R_flag()
    tests += get_tests_tR_flag()
    tests += get_tests_sorting()
    tests += get_tests_multiple_dirs()
    tests += get_tests_a_flag()
    tests += get_tests_rR_flag()
    tests += get_tests_r_flag()
    tests += get_tests_t_flag()
    tests += get_tests_l_flag()
    tests += get_tests_error_handling()
    tests += get_tests_aR_flag()
    tests += get_tests_alR_flag()
    tests += get_tests_perms()
    tests += get_tests_hyphen()
    tests += get_tests_hyphen_harder()
    tests += get_tests_symlink()
    tests += get_tests_multiple_files()
    tests += get_tests_special_bits()
    tests += get_tests_special_bits_dir()
    tests += get_tests_flags_mix()
    tests += get_tests_sys_usr_bin()
    tests += get_tests_sys_dev()
    tests += get_tests_sys_etc()
    tests += get_tests_sys_var_run()
    tests += get_tests_parsing()
    # tests += get_tests_bonus_non_printable()
    return tests
