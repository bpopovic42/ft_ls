from testing_utils.sandbox import Sandbox


def test_sys_etc_1():
    sandbox = Sandbox("test_sys_etc_1", "-l /etc")
    return sandbox.run()


def run_test_sys_etc():
    test_sys_etc_1()
