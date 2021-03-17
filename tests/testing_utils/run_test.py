import shutil
import os
import subprocess as sb

from testing_utils.globals import LS_PATH, FT_LS_PATH
from testing_utils.utils import make_new_unique_path

SHOULD_PRINT_DIFF = True
TEST_PASSED = 0
TEST_FAILED = 1
OKGREEN = '\033[92m'
FAIL = '\033[91m'
ENDC = '\033[0m'
RESULTS_DIR = os.path.join(os.path.dirname(__file__), "../results")

def print_return_value_diff(original_ls, ft_ls):
    print("Expected return value :\t" + OKGREEN + "{}".format(original_ls.returncode) + ENDC)
    print("Ft_ls return value:\t" + FAIL + "{}".format(ft_ls.returncode) + ENDC)

def print_stdout_diff(original_ls, ft_ls):
    test_results_dir = make_new_unique_path(RESULTS_DIR)
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


def run_test(sandbox, flags):
    original_ls = sb.run([LS_PATH, "-R", sandbox.path], capture_output=True)
    ft_ls = sb.run([FT_LS_PATH, "-R", sandbox.path], capture_output=True)
    test_result = compare(sandbox.name, original_ls, ft_ls)
    sandbox.clean()
    return test_result
