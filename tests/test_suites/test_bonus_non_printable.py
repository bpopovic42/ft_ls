from testing_utils.sandbox import Sandbox

# Most of those tests behave differently when ran directly from the command line

def test_bonus_non_printable_newline():
    sandbox = Sandbox("test_bonus_non_printable_newline", "\n")
    return sandbox.run()


def test_bonus_non_printable_yen():
    sandbox = Sandbox("test_bonus_non_printable_yen", ". \n")
    sandbox.cmd("touch ¥")
    return sandbox.run()


def test_bonus_non_printable_heart():
    sandbox = Sandbox("test_bonus_non_printable_heart", ". \n")
    sandbox.cmd("touch ❤️")
    return sandbox.run()


def test_bonus_buggy_quote_01():
    sandbox = Sandbox("test_bonus_buggy_quote_01", ".")
    sandbox.cmd("echo \"buggy\n'quote\" | xargs -0 touch")
    return sandbox.run()


def get_tests_bonus_non_printable():
    return (
        test_bonus_non_printable_newline,
        test_bonus_non_printable_yen,
        test_bonus_non_printable_heart,
        test_bonus_buggy_quote_01
    )
