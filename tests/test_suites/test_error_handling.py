from testing_utils.sandbox import Sandbox


# Ft_ls should not print anything to stdout and '' should be surrounded with double-quotes instead of simple ones
def test_error_handling_1():
    sandbox = Sandbox("test_error_handling_1", "''")
    sandbox.cmd("touch file")
    return sandbox.run()


def run_test_error_handling():
    test_error_handling_1()
