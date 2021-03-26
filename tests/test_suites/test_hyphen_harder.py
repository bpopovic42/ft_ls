from testing_utils.sandbox import Sandbox


def test_hyphen_harder_1():
    sandbox = Sandbox("test_hyphen_harder_1", "-- -- --")
    sandbox.cmd("touch -- - -- --")
    return sandbox.run()


def test_hyphen_harder_2():
    sandbox = Sandbox("test_hyphen_harder_2", "- - -")
    sandbox.cmd("")
    return sandbox.run()


def test_hyphen_harder_3():
    sandbox = Sandbox("test_hyphen_harder_3", "-- - -- ---")
    sandbox.cmd("")
    return sandbox.run()


def test_hyphen_harder_4():
    sandbox = Sandbox("test_hyphen_harder_4", "- -- ---")
    sandbox.cmd("")
    return sandbox.run()


def test_hyphen_harder_5():
    sandbox = Sandbox("test_hyphen_harder_5", "-- - ---")
    sandbox.cmd("")
    return sandbox.run()


def test_hyphen_harder_6():
    sandbox = Sandbox("test_hyphen_harder_6", "-- -- --")
    sandbox.cmd("mkdir -- - -- ---")
    return sandbox.run()


def run_test_hyphen_harder():
    test_hyphen_harder_1()
    test_hyphen_harder_2()
    test_hyphen_harder_3()
    test_hyphen_harder_4()
    test_hyphen_harder_5()
    test_hyphen_harder_6()
