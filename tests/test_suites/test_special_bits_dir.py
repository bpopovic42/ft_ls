from testing_utils.sandbox import Sandbox


def test_special_bits_dir_1():
    sandbox = Sandbox("test_special_bits_dir_1", "-l")
    sandbox.cmd("mkdir  dir1 && chmod 0777 dir1")
    return sandbox.run()


def test_special_bits_dir_2():
    sandbox = Sandbox("test_special_bits_dir_2", "-l")
    sandbox.cmd("mkdir  dir2 && chmod 1777 dir2")
    return sandbox.run()


def test_special_bits_dir_3():
    sandbox = Sandbox("test_special_bits_dir_3", "-l")
    sandbox.cmd("mkdir  dir3 && chmod 2777 dir3")
    return sandbox.run()


def test_special_bits_dir_4():
    sandbox = Sandbox("test_special_bits_dir_4", "-l")
    sandbox.cmd("mkdir  dir4 && chmod 3777 dir4")
    return sandbox.run()


def test_special_bits_dir_5():
    sandbox = Sandbox("test_special_bits_dir_5", "-l")
    sandbox.cmd("mkdir  dir5 && chmod 4777 dir5")
    return sandbox.run()


def test_special_bits_dir_6():
    sandbox = Sandbox("test_special_bits_dir_6", "-l")
    sandbox.cmd("mkdir  dir6 && chmod 5777 dir6")
    return sandbox.run()


def test_special_bits_dir_7():
    sandbox = Sandbox("test_special_bits_dir_7", "-l")
    sandbox.cmd("mkdir  dir7 && chmod 6777 dir7")
    return sandbox.run()


def test_special_bits_dir_8():
    sandbox = Sandbox("test_special_bits_dir_8", "-l")
    sandbox.cmd("mkdir  dir8 && chmod 7777 dir8")
    return sandbox.run()


def test_special_bits_dir_9():
    sandbox = Sandbox("test_special_bits_dir_9", "-l")
    sandbox.cmd("mkdir  dir9 && chmod 0000 dir9")
    return sandbox.run()


def test_special_bits_dir_10():
    sandbox = Sandbox("test_special_bits_dir_10", "-l")
    sandbox.cmd("mkdir  dir10 && chmod 1000 dir10")
    return sandbox.run()


def test_special_bits_dir_11():
    sandbox = Sandbox("test_special_bits_dir_11", "-l")
    sandbox.cmd("mkdir  dir11 && chmod 2000 dir11")
    return sandbox.run()


def test_special_bits_dir_12():
    sandbox = Sandbox("test_special_bits_dir_12", "-l")
    sandbox.cmd("mkdir  dir12 && chmod 3000 dir12")
    return sandbox.run()


def test_special_bits_dir_13():
    sandbox = Sandbox("test_special_bits_dir_13", "-l")
    sandbox.cmd("mkdir  dir13 && chmod 4000 dir13")
    return sandbox.run()


def test_special_bits_dir_14():
    sandbox = Sandbox("test_special_bits_dir_14", "-l")
    sandbox.cmd("mkdir  dir14 && chmod 5000 dir14")
    return sandbox.run()


def test_special_bits_dir_15():
    sandbox = Sandbox("test_special_bits_dir_15", "-l")
    sandbox.cmd("mkdir  dir15 && chmod 6000 dir15")
    return sandbox.run()


def test_special_bits_dir_16():
    sandbox = Sandbox("test_special_bits_dir_16", "-l")
    sandbox.cmd("mkdir  dir16 && chmod 7000 dir16")
    return sandbox.run()


def run_test_special_bits_dir():
    test_special_bits_dir_1()
    test_special_bits_dir_2()
    test_special_bits_dir_3()
    test_special_bits_dir_4()
    test_special_bits_dir_5()
    test_special_bits_dir_6()
    test_special_bits_dir_7()
    test_special_bits_dir_8()
    test_special_bits_dir_9()
    test_special_bits_dir_10()
    test_special_bits_dir_11()
    test_special_bits_dir_12()
    test_special_bits_dir_13()
    test_special_bits_dir_14()
    test_special_bits_dir_15()
    test_special_bits_dir_16()
