from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_simple_1():
    sandbox = Sandbox("test_simple_1")
    sandbox.run("touch aaa bbb ccc")
    return run_test(sandbox, "")


def test_simple_2():
    sandbox = Sandbox("test_simple_2")
    sandbox.run("touch - file")
    return run_test(sandbox, "")


def test_simple_3():
    sanbox = Sandbox("test_simple_3")
    sanbox.run("mkdir - dir")
    return run_test(sanbox, "")


def run_test_simple():
    test_simple_1()
    test_simple_2()
    test_simple_3()
