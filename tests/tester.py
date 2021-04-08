#!/usr/bin/env python3.8

import sys

import test_suites

from testing_utils.globals import SANDBOXES_DIR, COLOR_GREEN, COLOR_RED, COLOR_END
from testing_utils.utils import clean_existing_tests, process_cli_flags


def run_test_suites():
    tests = test_suites.get_all_tests()
    nbr_of_tests = 0
    succeeded_tests = 0
    for test in tests:
        test_result = test()
        nbr_of_tests += 1
        succeeded_tests += 1 if test_result else 0
    if succeeded_tests == nbr_of_tests:
        print("\nRESULT : " + COLOR_GREEN + "{}/{}\n".format(succeeded_tests, nbr_of_tests) + COLOR_END)
    else:
        print(
            "\nRESULT : " + COLOR_RED + "{}/{}".format(succeeded_tests, nbr_of_tests) + COLOR_END +
            " (See '{}/' for outputs)\n".format(SANDBOXES_DIR)
        )
    return nbr_of_tests, succeeded_tests


if __name__ == '__main__':
    process_cli_flags(sys.argv)
    clean_existing_tests()
    test_results = run_test_suites()
    if test_results[0] != test_results[1]:
        sys.exit(1)
    sys.exit(0)
