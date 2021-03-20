from testing_utils.sandbox import Sandbox


def test_a_flag_1():
    sandbox = Sandbox("test_a_flag_1", "-a")
    sandbox.cmd("mkdir .a a")
    return sandbox.run()


def test_a_flag_2():
    sandbox = Sandbox("test_a_flag_2", "-a")
    sandbox.cmd("mkdir .hiddendir{1..10} dir{1..10} && touch .hiddenfile{1..10} file{1..10}")
    return sandbox.run()


def run_test_a_flag():
    test_a_flag_1()
    test_a_flag_2()