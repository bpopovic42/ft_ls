from testing_utils.sandbox import Sandbox


def test_sys_usr_bin_1():
    sandbox = Sandbox("test_sys_usr_bin_1", "-lR /usr/bin")
    return sandbox.run()


def test_sys_usr_bin_2():
    sandbox = Sandbox("test_sys_usr_bin_2", "-l /usr")
    return sandbox.run()


def test_sys_usr_bin_3():
    sandbox = Sandbox("test_sys_usr_bin_3", "-t /usr")
    return sandbox.run()


def test_sys_usr_bin_4():
    sandbox = Sandbox("test_sys_usr_bin_4", "-tl /usr")
    return sandbox.run()


def get_tests_sys_usr_bin():
    return [
        test_sys_usr_bin_1,
        test_sys_usr_bin_2,
        test_sys_usr_bin_3,
        test_sys_usr_bin_4
    ]
