from testing_utils.sandbox import Sandbox


def test_simple_1():
    sandbox = Sandbox("test_simple_1", "")
    sandbox.cmd("touch aaa bbb ccc")
    return sandbox.run()


def test_simple_2():
    sandbox = Sandbox("test_simple_2", "")
    sandbox.cmd("touch - file")
    return sandbox.run()


def test_simple_3():
    sanbox = Sandbox("test_simple_3", "")
    sanbox.cmd("mkdir - dir")
    return sanbox.run()


# If a folder and a file are provided as arguments then folder path should be printed
def test_simple_4():
    sanbox = Sandbox("test_simple_4", ". file")
    sanbox.cmd("touch file")
    return sanbox.run()


def run_test_simple():
    test_simple_1()
    test_simple_2()
    test_simple_3()
    test_simple_4()
