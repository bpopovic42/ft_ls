from testing_utils.sandbox import Sandbox


def test_r_flag_1():
    sandbox = Sandbox("test_r_flag_1", "-r")
    sandbox.cmd("touch a b c AA BB CC")
    return sandbox.run()


def test_r_flag_2():
    sandbox = Sandbox("test_r_flag_2", "-r")
    sandbox.cmd("mkdir -p a b c AA BB CC")
    return sandbox.run()


def test_r_flag_3():
    sandbox = Sandbox("test_r_flag_3", "-r")
    sandbox.cmd("mkdir -p POP mok POPO liu && touch PIP mik PIPI lui")
    return sandbox.run()


def get_tests_r_flag():
    return (
        test_r_flag_1,
        test_r_flag_2,
        test_r_flag_3
    )
