from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_l_flag_1():
    sandbox = Sandbox("test_l_flag_1")
    sandbox.run("touch a b c && echo 'coucou' > a &&  echo 'hello world' > b")
    sandbox.run("mkdir 111 222 333 444 && touch 111/{a,b,c} && echo 'eat pizza' > 111/a")
    return run_test(sandbox, "l")


def test_l_flag_2():
    sandbox = Sandbox("test_l_flag_2")
    sandbox.run("touch file && xattr -w theAnswerIs42 whatever_you_want file")
    return run_test(sandbox, "-l")


def test_l_flag_padding():
    sandbox = Sandbox("test_l_flag_padding")
    sandbox.run("mkdir .test_dir")
    return run_test(sandbox, "-l")


def run_test_l_flag():
    test_l_flag_1()
    test_l_flag_2()
    test_l_flag_padding()
