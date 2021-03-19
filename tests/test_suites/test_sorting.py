from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_sorting_1():
    sandbox = Sandbox("test_sorting_1")
    sandbox.run("touch a b c AA BB CC")
    return run_test(sandbox, "")


def test_sorting_2():
    sandbox = Sandbox("test_sorting_2")
    sandbox.run("mkdir -p a b c AA BB CC")
    return run_test(sandbox, "")


def test_r_flag_3():
    sandbox = Sandbox("test_sorting_3")
    sandbox.run("mkdir -p da db dc dAA dBB dCC && touch fa fb fc fAA fBB fCC")
    return run_test(sandbox, "")


def run_test_sorting():
    test_sorting_1()
    test_sorting_2()
    test_r_flag_3()
