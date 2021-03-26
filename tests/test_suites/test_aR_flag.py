from testing_utils.sandbox import Sandbox


def test_aR_flag_1():
    sandbox = Sandbox("test_aR_flag_1", "-aR")
    sandbox.cmd("mkdir aRdir1 .aRhdir1")
    sandbox.cmd("touch .aRhdir1/file1 .aRhdir1/.hfile1")
    return sandbox.run()


def run_test_aR_flag():
    test_aR_flag_1()
