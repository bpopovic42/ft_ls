from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_rR_flag_1():
    sandbox = Sandbox("test_rR_flag_1")
    sandbox.run("mkdir -p level1_{1..2}/level2_{1..2}")
    return run_test(sandbox, "-rR")


def test_rR_flag_2():
    sandbox = Sandbox("test_rR_flag_2")
    sandbox.run("mkdir -p level1_{1..2}/level2_{1..2}/level3_{1..2}")
    return run_test(sandbox, "-rR")


def test_rR_flag_3():
    sandbox = Sandbox("test_rR_flag_3")
    sandbox.run("mkdir -p level1_{1..3}/level2_{6..8}/level3_{11..13}")
    return run_test(sandbox, "-rR")


def test_rR_flag_4():
    sandbox = Sandbox("test_rR_flag_4")
    sandbox.run("mkdir -p .a .b .c && mkdir -p a b c ")
    return run_test(sandbox, "-rR")


def run_test_rR_flag():
    test_rR_flag_1()
    test_rR_flag_2()
    test_rR_flag_3()
    test_rR_flag_4()
