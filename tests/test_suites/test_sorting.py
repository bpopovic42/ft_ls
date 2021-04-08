from testing_utils.sandbox import Sandbox


def test_sorting_1():
    sandbox = Sandbox("test_sorting_1", "")
    sandbox.cmd("touch a b c AA BB CC")
    return sandbox.run()


def test_sorting_2():
    sandbox = Sandbox("test_sorting_2", "")
    sandbox.cmd("mkdir -p a b c AA BB CC")
    return sandbox.run()


def test_r_flag_3():
    sandbox = Sandbox("test_sorting_3", "")
    sandbox.cmd("mkdir -p da db dc dAA dBB dCC && touch fa fb fc fAA fBB fCC")
    return sandbox.run()


def get_tests_sorting():
    return [
        test_sorting_1,
        test_sorting_2,
        test_r_flag_3
    ]
