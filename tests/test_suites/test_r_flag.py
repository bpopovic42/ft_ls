from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_r_flag_1():
    sandbox = Sandbox("test_r_flag_1")
    sandbox.run("touch a b c AA BB CC")
    return run_test(sandbox, "-r")


def test_r_flag_2():
    sandbox = Sandbox("test_r_flag_2")
    sandbox.run("mkdir -p a b c AA BB CC")
    return run_test(sandbox, "-r")


def test_r_flag_3():
    sandbox = Sandbox("test_r_flag_3")
    sandbox.run("mkdir -p POP mok POPO liu && touch PIP mik PIPI lui")
    return run_test(sandbox, "-r")


def run_test_r_flag():
    test_r_flag_1()
    test_r_flag_2()
    test_r_flag_3()
