from testing_utils.sandbox import Sandbox


def test_tR_flag_1():
    sandbox = Sandbox("test_tR_flag_1", "-tR")
    sandbox.cmd(
        "mkdir -p {} && "
        "mkdir -p {} && "
        "mkdir -p sbox/level1_1 sbox/level1_1/level2_1 && "
        "touch -t 201212101830.55 sbox/c_lvl1 && "
        "touch -t 201212101830.55 sbox/level1_1/c_lvl2 && "
        "touch -t 201212101830.55 sbox/level1_1/level2_1/c_lvl3".format(
            " ".join(["sbox/level1_" + str(n) + "/level2_" + str(n2) + "/level3_" + str(n3)
                      for n3 in range(1, 3) for n2 in range(1, 3) for n in range(1, 3)]),
            " ".join(["sbox1/level1_" + str(n) + "/level2_" + str(n2) + "/level3_" + str(n3)
                      for n3 in range(1, 3) for n2 in range(1, 3) for n in range(1, 3)]),
        )
    )
    return sandbox.run()


def get_tests_tR_flag():
    return [
        test_tR_flag_1
    ]
