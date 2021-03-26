from testing_utils.sandbox import Sandbox


def test_hyphen_1():
    sandbox = Sandbox("test_hyphen_1", "")
    sandbox.cmd("touch - file")
    return sandbox.run()


def test_hyphen_2():
    sandbox = Sandbox("test_hyphen_2", "-")
    sandbox.cmd("touch - file")
    return sandbox.run()


def test_hyphen_3():
    sandbox = Sandbox("test_hyphen_3", "--")
    sandbox.cmd("touch - file")
    return sandbox.run()


def test_hyphen_4():
    sandbox = Sandbox("test_hyphen_4", "-- -")
    sandbox.cmd("touch -")
    return sandbox.run()


def test_hyphen_5():
    sandbox = Sandbox("test_hyphen_5", "-- --")
    sandbox.cmd("touch - -- ---")
    return sandbox.run()


def test_hyphen_6():
    sandbox = Sandbox("test_hyphen_6", "-- ---")
    sandbox.cmd("touch - -- ---")
    return sandbox.run()


def test_hyphen_7():
    sandbox = Sandbox("test_hyphen_7", "-- .")
    sandbox.cmd("touch - -- ---")
    return sandbox.run()


def test_hyphen_8():
    sandbox = Sandbox("test_hyphen_8", "-- -file")
    sandbox.cmd("mkdir -- -file --file ---file")
    return sandbox.run()


def test_hyphen_9():
    sandbox = Sandbox("test_hyphen_9", "-- --file")
    sandbox.cmd("mkdir -- -file --file ---file")
    return sandbox.run()


def test_hyphen_10():
    sandbox = Sandbox("test_hyphen_10", "-- ---file")
    sandbox.cmd("mkdir -- -file --file ---file")
    return sandbox.run()


def test_hyphen_11():
    sandbox = Sandbox("test_hyphen_11", "")
    sandbox.cmd("mkdir -")
    return sandbox.run()


def test_hyphen_12():
    sandbox = Sandbox("test_hyphen_12", "-")
    sandbox.cmd("mkdir -")
    return sandbox.run()


def test_hyphen_13():
    sandbox = Sandbox("test_hyphen_13", "-- -")
    sandbox.cmd("mkdir -")
    return sandbox.run()


def test_hyphen_14():
    sandbox = Sandbox("test_hyphen_14", "-- --")
    sandbox.cmd("mkdir - -- ---")
    return sandbox.run()


def test_hyphen_15():
    sandbox = Sandbox("test_hyphen_15", "-- ---")
    sandbox.cmd("mkdir - -- ---")
    return sandbox.run()


def test_hyphen_16():
    sandbox = Sandbox("test_hyphen_16", "-- .")
    sandbox.cmd("mkdir - -- ---")
    return sandbox.run()


def test_hyphen_17():
    sandbox = Sandbox("test_hyphen_17", "-- -dir")
    sandbox.cmd("mkdir -- -dir --dir ---dir")
    return sandbox.run()


def test_hyphen_18():
    sandbox = Sandbox("test_hyphen_18", "-- --dir")
    sandbox.cmd("mkdir -- -dir --dir ---dir")
    return sandbox.run()


def test_hyphen_19():
    sandbox = Sandbox("test_hyphen_19", "-- ---dir")
    sandbox.cmd("mkdir -- -dir --dir ---dir")
    return sandbox.run()


def run_test_hyphen():
    test_hyphen_1()
    test_hyphen_2()
    test_hyphen_3()
    test_hyphen_4()
    test_hyphen_5()
    test_hyphen_6()
    test_hyphen_7()
    test_hyphen_8()
    test_hyphen_9()
    test_hyphen_10()
    test_hyphen_11()
    test_hyphen_12()
    test_hyphen_13()
    test_hyphen_14()
    test_hyphen_15()
    test_hyphen_16()
    test_hyphen_17()
    test_hyphen_18()
    test_hyphen_19()
