from testing_utils.sandbox import Sandbox


def test_tR_flag_1():
    sandbox = Sandbox("test_tR_flag_1", "-tR")
    sandbox.cmd(
        "mkdir -p sbox/level1_{1..2}/level2_{1..2}/level3_{1..2} && "
        "mkdir -p sbox1/level1_{1..2}/level2_{1..2}/level3_{1..2} && "
        "mkdir -p sbox/level1_1 sbox/level1_1/level2_1 && "
        "touch -t 201212101830.55 sbox/c_lvl1 && "
        "touch -t 201212101830.55 sbox/level1_1/c_lvl2 && "
        "touch -t 201212101830.55 sbox/level1_1/level2_1/c_lvl3"
    )
    return sandbox.run()


def run_tR_flag():
    test_tR_flag_1()
