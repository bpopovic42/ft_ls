from testing_utils.sandbox import Sandbox


def test_t_flag_1():
    sandbox = Sandbox("test_t_flag_1", "-t")
    sandbox.cmd("touch a b c d e && touch -t 201212101830.55 c")
    return sandbox.run()


def test_t_flag_2():
    sandbox = Sandbox("test_t_flag_2", "-t")
    sandbox.cmd("touch -t 201312101830.55 a && touch -t 201212101830.55 b && touch -t 201412101830.55 c")
    return sandbox.run()


def test_t_flag_3():
    sandbox = Sandbox("test_t_flag_3", "-t")
    sandbox.cmd("touch {} {} {} && touch -t 200012101830.55 {}".format(
        " ".join(["fileA" + str(n) for n in range(1, 6)]),
        " ".join(["fileB" + str(n) for n in range(1, 6)]),
        " ".join(["fileC" + str(n) for n in range(1, 6)]),
        " ".join(["fileA" + str(n) for n in range(1, 6)]),
    ))
    return sandbox.run()


def test_t_flag_4():
    sandbox = Sandbox("test_t_flag_4", "-t")
    sandbox.cmd(
        "touch -t 201312101830.55 a && "
        "touch -t 201212101830.55 b && "
        "touch -t 201412101830.55 c && "
        "touch -t 201411221830.55 d && "
        "touch -t 201405212033.55 e && "
        "touch -t 201409221830.55 f && "
        "touch -t 202007221830.55 g && "
        "touch -t 300012101830.55 h"
    )
    return sandbox.run()


def test_t_flag_5():
    sandbox = Sandbox("test_t_flag_5", "-t")
    sandbox.cmd(
        "touch -t 200012101830.55 a && "
        "touch -t 201412101830.55 b && "
        "ln b d && "
        "ln -s c e && "
        "ln -s a f && "
        "touch -t 300012101830.55 c"
    )
    return sandbox.run()


def test_t_flag_6():
    sandbox = Sandbox("test_t_flag_6", "-t")
    sandbox.cmd("mkdir -p {}".format(
        " ".join(["level1_" + str(n) + "/level2_" + str(n2) for n2 in range (1, 3) for n in range(1, 3)])
    ))
    sandbox.cmd(
        "touch -t 201312101830.55 B && "
        "touch -t 201312101830.55 a"
    )
    return sandbox.run()


def test_t_flag_7():
    sandbox = Sandbox("test_t_flag_7", "-t")
    sandbox.cmd(
        "touch C && touch -t 201212101830.55 c && mkdir -p sbox sbox1 && "
        "touch -t 201312101830.55 B && "
        "touch -t 201312101830.55 a"
    )
    return sandbox.run()


def run_test_t_flag():
    test_t_flag_1()
    test_t_flag_2()
    test_t_flag_3()
    test_t_flag_4()
    test_t_flag_5()
    test_t_flag_6()
    test_t_flag_7()
