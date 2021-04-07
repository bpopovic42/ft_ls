from testing_utils.sandbox import Sandbox


def test_special_bits_1():
    sandbox = Sandbox("test_special_bits_1", "-l")
    sandbox.cmd("touch file1 && chmod 0777 file1")
    return sandbox.run()


def test_special_bits_2():
    sandbox = Sandbox("test_special_bits_2", "-l")
    sandbox.cmd("touch file2 && chmod 1777 file2")
    return sandbox.run()


def test_special_bits_3():
    sandbox = Sandbox("test_special_bits_3", "-l")
    sandbox.cmd("touch file3 && chmod 2777 file3")
    return sandbox.run()


def test_special_bits_4():
    sandbox = Sandbox("test_special_bits_4", "-l")
    sandbox.cmd("touch file4 && chmod 3777 file4")
    return sandbox.run()


def test_special_bits_5():
    sandbox = Sandbox("test_special_bits_5", "-l")
    sandbox.cmd("touch file5 && chmod 4777 file5")
    return sandbox.run()


def test_special_bits_6():
    sandbox = Sandbox("test_special_bits_6", "-l")
    sandbox.cmd("touch file6 && chmod 5777 file6")
    return sandbox.run()


def test_special_bits_7():
    sandbox = Sandbox("test_special_bits_7", "-l")
    sandbox.cmd("touch file7 && chmod 6777 file7")
    return sandbox.run()


def test_special_bits_8():
    sandbox = Sandbox("test_special_bits_8", "-l")
    sandbox.cmd("touch file8 && chmod 7777 file8")
    return sandbox.run()


def test_special_bits_9():
    sandbox = Sandbox("test_special_bits_9", "-l")
    sandbox.cmd("touch file9 && chmod 0000 file9")
    return sandbox.run()


def test_special_bits_10():
    sandbox = Sandbox("test_special_bits_10", "-l")
    sandbox.cmd("touch file10 && chmod 1000 file10")
    return sandbox.run()


def test_special_bits_11():
    sandbox = Sandbox("test_special_bits_11", "-l")
    sandbox.cmd("touch file11 && chmod 2000 file11")
    return sandbox.run()


def test_special_bits_12():
    sandbox = Sandbox("test_special_bits_12", "-l")
    sandbox.cmd("touch file12 && chmod 3000 file12")
    return sandbox.run()


def test_special_bits_13():
    sandbox = Sandbox("test_special_bits_13", "-l")
    sandbox.cmd("touch file13 && chmod 4000 file13")
    return sandbox.run()


def test_special_bits_14():
    sandbox = Sandbox("test_special_bits_14", "-l")
    sandbox.cmd("touch file14 && chmod 5000 file14")
    return sandbox.run()


def test_special_bits_15():
    sandbox = Sandbox("test_special_bits_15", "-l")
    sandbox.cmd("touch file15 && chmod 6000 file15")
    return sandbox.run()


def test_special_bits_16():
    sandbox = Sandbox("test_special_bits_16", "-l")
    sandbox.cmd("touch file16 && chmod 7000 file16")
    return sandbox.run()


def run_test_special_bits():
    test_special_bits_1()
    test_special_bits_2()
    test_special_bits_3()
    test_special_bits_4()
    test_special_bits_5()
    test_special_bits_6()
    test_special_bits_7()
    test_special_bits_8()
    test_special_bits_9()
    test_special_bits_10()
    test_special_bits_11()
    test_special_bits_12()
    test_special_bits_13()
    test_special_bits_14()
    test_special_bits_15()
    test_special_bits_16()
