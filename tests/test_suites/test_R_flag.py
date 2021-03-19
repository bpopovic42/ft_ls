import os

from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_R_flag_1():
    sandbox = Sandbox("test_R_flag_1")
    sandbox.run("mkdir -p level1_{1..2}/level2_{1..2}/level3_{1..2}")
    return run_test(sandbox, "-R")


def test_R_flag_2():
    sandbox = Sandbox("test_R_flag_2")
    sandbox.run("mkdir -p level1_{1..3}/level2_{6..8}/level3_{11..13}")
    return run_test(sandbox, "-R")


def test_R_flag_3():
    sandbox = Sandbox("test_R_flag_3")
    sandbox.run("mkdir -p .a .b .c && mkdir -p a b c ")
    return run_test(sandbox, "-R")


def test_R_flag_4():
    sandbox = Sandbox("test_R_flag_4")
    sandbox.run("mkdir a b c")
    sandbox.run("chmod 000 b")
    return run_test(sandbox, "-1R 2>&1 | grep -v denied")


def test_R_flag_5():
    sandbox = Sandbox("test_R_flag_5")
    sandbox.run("mkdir a b c")
    sandbox.run("chmod 000 b")
    return run_test(sandbox, "-1R 2>&1 | grep denied | wc -l | tr -d ' ' | tr -d '\n'")


def test_R_flag_6():
    sandbox = Sandbox("test_R_flag_6")
    sandbox.run("mkdir A")
    sandbox.run("touch A/file")
    return run_test(sandbox, "-1R A a")


def test_R_flag_7():
    sandbox = Sandbox("test_R_flag_7")
    sandbox.run("mkdir A")
    sandbox.run("touch A/file rootfile")
    return run_test(sandbox, "-1R A a rootfile rootfile")


def test_recursion():
    sandbox = Sandbox("test_recursion")
    current_dir = os.getcwd()
    os.chdir(sandbox.path)
    for i in range(800):
        os.mkdir("subdir" + str(i))
        os.chdir("subdir" + str(i))
    os.chdir(current_dir)
    return run_test(sandbox, "-R")


def run_test_R_flag():
    test_R_flag_1()
    test_R_flag_2()
    test_R_flag_3()
    test_R_flag_4()
    test_R_flag_5()
    test_R_flag_6()
    test_R_flag_7()
    test_recursion()
