from testing_utils.sandbox import Sandbox


def test_rR_flag_1():
    sandbox = Sandbox("test_rR_flag_1", "-rR")
    sandbox.cmd("mkdir -p {}".format(
        " ".join(["level_1" + str(n) + "/level2_" + str(n2)
                  for n2 in range(1, 3) for n in range(1, 3)])
    ))
    return sandbox.run()


def test_rR_flag_2():
    sandbox = Sandbox("test_rR_flag_2", "-rR")
    sandbox.cmd("mkdir -p {}".format(
        " ".join(["level_1" + str(n) + "/level2_" + str(n2) + "/level3_" + str(n3)
                  for n3 in range(1, 3) for n2 in range(1, 3) for n in range(1, 3)])
    ))
    return sandbox.run()


def test_rR_flag_3():
    sandbox = Sandbox("test_rR_flag_3", "-rR")
    sandbox.cmd("mkdir -p {}".format(
        " ".join(["level_1" + str(n) + "/level2_" + str(n2) + "/level3_" + str(n3)
                  for n3 in range(11, 14) for n2 in range(6, 9) for n in range(1, 4)])
    ))
    return sandbox.run()


def test_rR_flag_4():
    sandbox = Sandbox("test_rR_flag_4", "-rR")
    sandbox.cmd("mkdir -p .a .b .c && mkdir -p a b c ")
    return sandbox.run()


def get_tests_rR_flag():
    return (
        test_rR_flag_1,
        test_rR_flag_2,
        test_rR_flag_3,
        test_rR_flag_4
    )
