from testing_utils.sandbox import Sandbox


def test_perms_1():
    sandbox = Sandbox("test_perms_1", "-l")
    sandbox.cmd("touch a b c")
    sandbox.cmd("chmod 644 a")
    sandbox.cmd("chmod 755 b")
    sandbox.cmd("chmod 311 c")
    return sandbox.run()


def test_perms_2():
    sandbox = Sandbox("test_perms_2", "-l")
    sandbox.cmd("mkdir a b c")
    sandbox.cmd("chmod 644 a")
    sandbox.cmd("chmod 755 b")
    sandbox.cmd("chmod 311 c")
    return sandbox.run()


def get_tests_perms():
    return (
        test_perms_1,
        test_perms_2
    )
