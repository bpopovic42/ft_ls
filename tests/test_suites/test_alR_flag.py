from testing_utils.sandbox import Sandbox


def test_alR_flag_1():
    sandbox = Sandbox("test_alR_flag_1", "-alR")
    sandbox.cmd("mkdir .hdir")
    return sandbox.run()


def run_test_alR_flag():
    test_alR_flag_1()
