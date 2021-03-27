from testing_utils.sandbox import Sandbox


def test_non_printable_newline():
    sandbox = Sandbox("test_non_printable_newline", "\n")
    return sandbox.run()


# This doesn't work from command line
def test_non_printable_yen():
    sandbox = Sandbox("test_non_printable_yen", ". \n")
    sandbox.cmd("touch ¥")
    return sandbox.run()


def run_test_non_printable():
    test_non_printable_newline()
    test_non_printable_yen()
