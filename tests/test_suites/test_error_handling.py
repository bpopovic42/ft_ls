from testing_utils.sandbox import Sandbox


# Ft_ls should not print anything to stdout and '' should be surrounded with double-quotes instead of simple ones
def test_error_handling_1():
    sandbox = Sandbox("test_error_handling_1", "''")
    sandbox.cmd("touch file")
    return sandbox.run()


def test_error_handling_2():
    sandbox = Sandbox("test_error_handling_2", "-R 2>&1 | grep denied | wc -l | tr -d ' ' | tr -d '\n'")
    sandbox.cmd("mkdir a b c")
    sandbox.cmd("chmod 000 b")
    return sandbox.run()


def run_test_error_handling():
    test_error_handling_1()
