from testing_utils.sandbox import Sandbox


def test_aR_flag_1():
    sandbox = Sandbox("test_aR_flag_1", "-aR")
    sandbox.cmd("mkdir aRdir1 .aRhdir1")
    sandbox.cmd("touch .aRhdir1/file1 .aRhdir1/.hfile1")
    return sandbox.run()


def get_tests_aR_flag():
    return [
        test_aR_flag_1
    ]
