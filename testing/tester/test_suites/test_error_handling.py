from testing_utils.sandbox import Sandbox


# Ft_ls should not print anything to stdout and '' should be surrounded with double-quotes instead of simple ones
def test_error_handling_1():
    sandbox = Sandbox("test_error_handling_1", "''")
    sandbox.cmd("touch file")
    return sandbox.run()


# Invalid arguments (program arguments are not interpreted as commands in this tester)
def test_error_handling_2():
    sandbox = Sandbox("test_error_handling_2", "-R 2>&1 | grep denied | wc -l | tr ' '")
    sandbox.cmd("mkdir a b c")
    sandbox.cmd("chmod 000 b")
    return sandbox.run()


def test_error_handling_3():
    sandbox = Sandbox("test_error_handling_3", "unallowed_file")
    sandbox.cmd("touch unallowed_file")
    sandbox.cmd("chmod 000 unallowed_file")
    return sandbox.run()


def test_error_handling_4():
    sandbox = Sandbox("test_error_handling_4", "-_bad_flag")
    return sandbox.run()


def test_error_handling_5():
    sandbox = Sandbox("test_error_handling_5", "-la--t")
    return sandbox.run()


def test_error_handling_6():
    sandbox = Sandbox("test_error_handling_6", "--j")
    return sandbox.run()


def test_error_handling_7():
    sandbox = Sandbox("test_error_handling_7", "\"\"")
    return sandbox.run()


def test_error_handling_8():
    sandbox = Sandbox("test_error_handling_8", "''")
    return sandbox.run()


def test_error_handling_9():
    sandbox = Sandbox("test_error_handling_9", "a '' b")
    sandbox.cmd("touch a b")
    return sandbox.run()


def test_error_handling_10():
    sandbox = Sandbox("test_error_handling_10", "-lWZYX243")
    return sandbox.run()


def test_error_handling_11():
    sandbox = Sandbox("test_error_handling_11", "a b")
    return sandbox.run()


def test_error_handling_12():
    sandbox = Sandbox("test_error_handling_12", "a b")
    sandbox.cmd("mkdir b")
    return sandbox.run()


def test_error_handling_13():
    sandbox = Sandbox("test_error_handling_13",
                      "adir zdir aNotExist zNotExistB afile zfile asymdir zsymdir asymfile zsymfile")
    sandbox.cmd("mkdir adir zdir")
    sandbox.cmd("touch afile zfile")
    sandbox.cmd("ln -s adir asymdir")
    sandbox.cmd("ln -s adir zsymdir")
    sandbox.cmd("ln -s afile asymfile")
    sandbox.cmd("ln -s afile zsymfile")
    return sandbox.run()


def test_error_handling_14():
    sandbox = Sandbox("test_error_handling_14", "-r a c b l K j")
    sandbox.cmd("touch K j l")
    return sandbox.run()


def test_error_handling_15():
    sandbox = Sandbox("test_error_handling_15", "\"\"")
    return sandbox.run()


def test_error_handling_16():
    sandbox = Sandbox("test_error_handling_16", "-l \\\"\\\"")
    return sandbox.run()


def test_error_handling_17():
    sandbox = Sandbox("test_error_handling_17", "-l ''")
    return sandbox.run()


def test_error_handling_18():
    sandbox = Sandbox("test_error_handling_18", "-l \"\" -R")
    return sandbox.run()


def test_error_handling_19():
    sandbox = Sandbox("test_error_handling_19", "-lR . \"\" .")
    return sandbox.run()


def test_error_handling_20():
    sandbox = Sandbox("test_error_handling_20", "-~ \"\"")
    return sandbox.run()


def test_error_handling_21():
    sandbox = Sandbox("test_error_handling_21", "\"\" -~")
    return sandbox.run()


def test_error_handling_22():
    sandbox = Sandbox("test_error_handling_22", "aa \"\" bb")
    return sandbox.run()


def test_error_handling_23():
    sandbox = Sandbox("test_error_handling_23", "\"\" aa bb")
    return sandbox.run()


def test_error_handling_24():
    sandbox = Sandbox("test_error_handling_24", "aa bb \"\"")
    return sandbox.run()


def test_error_handling_25():
    sandbox = Sandbox("test_error_handling_25", "a \"\" b")
    return sandbox.run()


def test_error_handling_26():
    sandbox = Sandbox("test_error_handling_26", ". \"\"")
    return sandbox.run()


def get_tests_error_handling():
    return (
        test_error_handling_1,
        test_error_handling_2,
        test_error_handling_3,
        test_error_handling_4,
        test_error_handling_5,
        test_error_handling_6,
        test_error_handling_7,
        test_error_handling_8,
        test_error_handling_9,
        test_error_handling_10,
        test_error_handling_11,
        test_error_handling_12,
        test_error_handling_13,
        test_error_handling_14,
        test_error_handling_15,
        test_error_handling_16,
        test_error_handling_17,
        test_error_handling_18,
        test_error_handling_19,
        test_error_handling_20,
        test_error_handling_21,
        test_error_handling_22,
        test_error_handling_23,
        test_error_handling_24,
        test_error_handling_25,
        test_error_handling_26
    )
