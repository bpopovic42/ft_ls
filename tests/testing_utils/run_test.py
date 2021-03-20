import os
import subprocess as sb

from testing_utils.globals import LS_PATH, FT_LS_PATH
from testing_utils.utils import get_new_folder
from testing_utils.utils import write_process_stdout_to_file

from testing_utils.globals import RESULTS_DIR

TEST_PASSED = 0
TEST_FAILED = 1


def record_return_values(original_ls, ft_ls, destination_file):
    expected_return_value = "Expected return value :\t {}".format(original_ls.returncode)
    ft_ls_return_value = "Ft_ls return value :\t {}".format(ft_ls.returncode)
    destination_file.write(expected_return_value + "\n")
    destination_file.write(ft_ls_return_value + "\n")
    if SHOULD_PRINT_DIFF:
        print(expected_return_value)
        print(ft_ls_return_value)


def record_stdout(original_ls, ft_ls, recording_destination_folder):
    ls_output_file_path = recording_destination_folder + "/" + "ls_out"
    write_process_stdout_to_file(original_ls, ls_output_file_path)
    ft_ls_output_file_path = recording_destination_folder + "/" + "ft_ls_out"
    write_process_stdout_to_file(ft_ls, ft_ls_output_file_path)
    if SHOULD_PRINT_DIFF:
        os.system("diff -u " + ls_output_file_path + " " + ft_ls_output_file_path + " | ydiff -s -p cat")


def record_results(recording_destination_folder, original_ls, ft_ls, arguments):
    info_file_path = recording_destination_folder + "/" + "info"
    info_file = open(info_file_path, "a+")
    info_file.write("Arguments :\t\t " + arguments + "\n")
    record_return_values(original_ls, ft_ls, info_file)
    info_file.close()
    record_stdout(original_ls, ft_ls, recording_destination_folder)


def compare(test_name, original_ls, ft_ls):
    returncode_matches = ft_ls.returncode == original_ls.returncode
    stdout_matches = ft_ls.stdout.decode("utf-8") == original_ls.stdout.decode("utf-8")
    if returncode_matches and stdout_matches:
        return TEST_PASSED
    else:
        return TEST_FAILED


def run_test(sandbox, arguments):
    original_ls = sb.run([LS_PATH] + arguments.split(), cwd=sandbox.path, capture_output=True)
    ft_ls = sb.run([FT_LS_PATH] + arguments.split(), cwd=sandbox.path, capture_output=True)
    test_result = compare(sandbox.name, original_ls, ft_ls)
    if test_result == TEST_PASSED:
        print("{}: ".format(sandbox.name).ljust(40, " ") + OKGREEN + "PASSED" + ENDC)
    else:
        results_destination = get_new_folder(RESULTS_DIR, sandbox.name)
        print("{}: ".format(sandbox.name).ljust(40, " ") + FAIL + "FAILED " + ENDC)
        record_results(results_destination, original_ls, ft_ls, arguments)
    sandbox.clean()
    return test_result
