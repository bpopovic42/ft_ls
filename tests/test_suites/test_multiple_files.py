from testing_utils.sandbox import Sandbox


def test_multiple_files_1():
    sandbox = Sandbox("test_multiple_files_1", ". .")
    return sandbox.run()


def test_multiple_files_2():
    sandbox = Sandbox("test_multiple_files_2", "./ .")
    sandbox.cmd("touch a b C D")
    return sandbox.run()


def test_multiple_files_3():
    sandbox = Sandbox("test_multiple_files_3", "z b a c d f e")
    sandbox.cmd("touch a c z")
    sandbox.cmd("mkdir b d")
    sandbox.cmd("ln -s a e && ln -s a f")
    return sandbox.run()


def test_multiple_files_4():
    sandbox = Sandbox("test_multiple_files_4", "-l")
    sandbox.cmd("touch {}".format(
        " ".join(["file_" + str(n) for n in range(0, 1000)])
    ))
    return sandbox.run()


def get_tests_multiple_files():
    return (
        test_multiple_files_1,
        test_multiple_files_2,
        test_multiple_files_3,
        test_multiple_files_4
    )
