#!/usr/bin/env python3.8

import os
import sys
import subprocess as sb

from datetime import datetime
from uuid import uuid4


ORIGINAL_LS = sb.check_output(["which", "ls"]).decode("utf-8").replace("\n", "")
FT_LS = os.path.join(os.path.dirname(__file__), "../ft_ls/ft_ls")
RESULTS_DIR = os.path.join(os.path.dirname(__file__), "results")
SHOULD_PRINT_DIFF = True
OKGREEN = '\033[92m'
FAIL = '\033[91m'
ENDC = '\033[0m'
TEST_PASSED = 0
TEST_FAILED = 1


def print_return_value_diff(original_ls, ft_ls):
    print("Expected return value :\t" + OKGREEN + "{}".format(original_ls.returncode) + ENDC)
    print("Ft_ls return value:\t" + FAIL + "{}".format(ft_ls.returncode) + ENDC)

def print_stdout_diff(original_ls, ft_ls):
    eventid = datetime.now().strftime('%Y%m-%d%H-%M%S-') + str(uuid4())
    test_results_dir = RESULTS_DIR + "/" + eventid
    os.mkdir(test_results_dir)
    ls_output_file_path = test_results_dir + "/" + "ls_out"
    ls_output_file = open(test_results_dir + "/" + "ls_out", "w+")
    ls_output_file.write(original_ls.stdout.decode("utf-8"))
    ls_output_file.close()
    ft_ls_output_file_path = test_results_dir + "/" + "ft_ls_out"
    ft_ls_output_file = open(test_results_dir + "/" + "ft_ls_out", "w+")
    ft_ls_output_file.write(ft_ls.stdout.decode("utf-8"))
    ft_ls_output_file.close()
    os.system("diff -u " + ls_output_file_path + " " + ft_ls_output_file_path + " | ydiff -s -p cat")
    os.remove(ft_ls_output_file_path)
    os.remove(ls_output_file_path)
    os.rmdir(test_results_dir)


def compare(test_name, original_ls, ft_ls):
    returncode_matches = ft_ls.returncode == original_ls.returncode
    stdout_matches = ft_ls.stdout.decode("utf-8") == original_ls.stdout.decode("utf-8")
    if returncode_matches and stdout_matches:
        print("TEST '{}' ".format(test_name) + OKGREEN + "PASSED" + ENDC)
        return TEST_PASSED
    else:
        print("TEST '{}' ".format(test_name) + FAIL + "FAILED" + ENDC)
        if SHOULD_PRINT_DIFF:
            if not returncode_matches: print_return_value_diff(original_ls, ft_ls)
            if not stdout_matches: print_stdout_diff(original_ls, ft_ls)
        return TEST_FAILED



def test_from_cli(arguments):
    original_ls = sb.run([ORIGINAL_LS] + arguments, capture_output=True)
    ft_ls  = sb.run([FT_LS] + arguments, capture_output=True)
    compare(" ".join(arguments), original_ls, ft_ls)

def test_l_flag_simple():
    files = []
    test_name = "test_l_flag_simple"
    SANDBOX = os.path.join(os.path.dirname(__file__), "sandbox")
    eventid = datetime.now().strftime('%Y%m-%d%H-%M%S-') + str(uuid4())
    test_folder = SANDBOX + "/" + eventid
    os.mkdir(test_folder)
    for i in range(10):
        file_name = test_folder + "/" + str(i)
        open(file_name, "w+")
        files.append(file_name)
    original_ls = sb.run([ORIGINAL_LS, "-l", test_folder], capture_output=True)
    ft_ls  = sb.run([FT_LS, "-l", test_folder], capture_output=True)
    test_status = compare(test_name, original_ls, ft_ls)
    for file in files:
        os.remove(file)
    os.rmdir(test_folder)
    return test_status


def run_test_suites():
    test_l_flag_simple()

if __name__ == '__main__':
    if len(sys.argv) > 1:
        test_from_cli(sys.argv[1:])
    else:
        run_test_suites()
