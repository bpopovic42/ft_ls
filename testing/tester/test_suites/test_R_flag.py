import os

from testing_utils.sandbox import Sandbox


def test_R_flag_1():
    sandbox = Sandbox("test_R_flag_1", "-R")
    sandbox.cmd("mkdir -p {}".format(
        " ".join(["level1_" + str(n) + "/level2_" + str(n2) + "/level3_" + str(n3)
                 for n3 in range(1, 3) for n2 in range(1, 3) for n in range(1, 3)])
    ))
    return sandbox.run()


def test_R_flag_2():
    sandbox = Sandbox("test_R_flag_2", "-R")
    sandbox.cmd("mkdir -p {}".format(
        " ".join(["level1_" + str(n) + "/level2_" + str(n2) + "/level3_" + str(n3)
                   for n3 in range(11, 14) for n2 in range(6, 9) for n in range(1, 4)])
    ))
    return sandbox.run()


def test_R_flag_3():
    sandbox = Sandbox("test_R_flag_3", "-R")
    sandbox.cmd("mkdir -p .a .b .c && mkdir -p a b c ")
    return sandbox.run()


def test_R_flag_4():
    sandbox = Sandbox("test_R_flag_4", "-R")
    sandbox.cmd("mkdir a b c")
    sandbox.cmd("chmod 000 b")
    return sandbox.run()


def test_R_flag_5():
    sandbox = Sandbox("test_R_flag_5", "-R")
    sandbox.cmd("mkdir a b c")
    sandbox.cmd("chmod 000 b")
    return sandbox.run()


def test_R_flag_6():
    sandbox = Sandbox("test_R_flag_6", "-R A a")
    sandbox.cmd("mkdir A")
    sandbox.cmd("touch A/file")
    return sandbox.run()


def test_R_flag_7():
    sandbox = Sandbox("test_R_flag_7", "-R A a rootfile rootfile")
    sandbox.cmd("mkdir A")
    sandbox.cmd("touch A/file rootfile")
    return sandbox.run()


def test_recursion():
    sandbox = Sandbox("test_recursion", "-R")
    current_dir = os.getcwd()
    os.chdir(sandbox.path)
    for i in range(800):
        os.mkdir("subdir" + str(i))
        os.chdir("subdir" + str(i))
    os.chdir(current_dir)
    return sandbox.run()


def get_tests_R_flag():
    return (
        test_R_flag_1,
        test_R_flag_2,
        test_R_flag_3,
        test_R_flag_4,
        test_R_flag_5,
        test_R_flag_6,
        test_R_flag_7,
        test_recursion
    )
