from testing_utils.sandbox import Sandbox


def test_sys_dev_1():
    sandbox = Sandbox("test_sys_dev_1", "/dev")
    return sandbox.run()


def test_sys_dev_2():
    sandbox = Sandbox("test_sys_dev_2", "-l /dev")
    return sandbox.run()


def test_sys_dev_3():
    sandbox = Sandbox("test_sys_dev_3", "-la /dev")
    return sandbox.run()


def get_tests_sys_dev():
    return [
        test_sys_dev_1,
        test_sys_dev_2,
        test_sys_dev_3
    ]
