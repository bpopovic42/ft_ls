from testing_utils.sandbox import Sandbox


def test_sys_var_run_1():
    sandbox = Sandbox("test_sys_var_run_1", "-l /var/run")
    return sandbox.run()


def run_test_sys_var_run():
    test_sys_var_run_1()
