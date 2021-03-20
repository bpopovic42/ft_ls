from testing_utils.sandbox import Sandbox


def test_multiple_dirs_1():
    sandbox = Sandbox("test_multiple_dirs_1", "mydir mydir2")
    sandbox.cmd("mkdir mydir mydir2 && touch mydir/{aaa,bbb,ccc} && touch mydir2/{111,222,333}")
    return sandbox.run()


def test_multiple_dirs_2():
    sandbox = Sandbox("test_multiple_dirs_2", "mydir mydir2")
    sandbox.cmd("mkdir mydir mydir2 && touch mydir/file{10..20} && touch mydir2/file{30..40}")
    return sandbox.run()


def test_multiple_dirs_3():
    sandbox = Sandbox("test_multiple_dirs_3", "mydir{1..7}")
    sandbox.cmd("mkdir mydir{1..7} && touch mydir{1..7}/file{1..11}")
    return sandbox.run()


def test_multiple_dirs_4():
    sandbox = Sandbox("test_multiple_dirs_4", "mydir")
    sandbox.cmd("mkdir mydir && touch mydir/a")
    return sandbox.run()


def run_test_multiple_dirs():
    test_multiple_dirs_1()
    test_multiple_dirs_2()
    test_multiple_dirs_3()
    test_multiple_dirs_4()
