from testing_utils.sandbox import Sandbox


def test_a_flag_1():
    sandbox = Sandbox("test_a_flag_1", "-a")
    sandbox.cmd("mkdir .a a")
    return sandbox.run()


def test_a_flag_2():
    sandbox = Sandbox("test_a_flag_2", "-a")
    sandbox.cmd("mkdir {} {} && touch {} {}".format(
        " ".join([".hiddendir" + str(n) for n in range(1, 11)]),
        " ".join(["dir" + str(n) for n in range(1, 11)]),
        " ".join([".hiddenfile" + str(n) for n in range(1, 11)]),
        " ".join(["file" + str(n) for n in range(1, 11)])
    ))
    return sandbox.run()


def get_tests_a_flag():
    return [
        test_a_flag_1,
        test_a_flag_2
    ]