import os
from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_recursion():
    sandbox = Sandbox("test_subdir")
    current_dir = os.getcwd()
    os.chdir(sandbox.path)
    for i in range(800):
        os.mkdir("subdir" + str(i))
        os.chdir("subdir" + str(i))
    os.chdir(current_dir)
    return run_test(sandbox, "-R")


def run_test_r_flag():
    test_recursion()