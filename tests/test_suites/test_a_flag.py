from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_a_flag_1():
    sandbox = Sandbox("test_a_flag_1")
    sandbox.run("mkdir .a a")
    return run_test(sandbox, "-a")


def test_a_flag_2():
    sandbox = Sandbox("test_a_flag_2")
    sandbox.run("mkdir .hiddendir{1..10} dir{1..10} && touch .hiddenfile{1..10} file{1..10}")
    return run_test(sandbox, "-a")


def run_test_a_flag():
    test_a_flag_1()
    test_a_flag_2()