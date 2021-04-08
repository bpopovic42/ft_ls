from testing_utils.sandbox import Sandbox


def test_sys_etc_1():
    sandbox = Sandbox("test_sys_etc_1", "-l /etc")
    return sandbox.run()


def get_tests_sys_etc():
    return [
        test_sys_etc_1
    ]
