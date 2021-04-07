from testing_utils.sandbox import Sandbox


def test_multiple_dirs_1():
    sandbox = Sandbox("test_multiple_dirs_1", "mydir mydir2")
    sandbox.cmd("mkdir mydir mydir2")
    sandbox.cmd("touch mydir/aaa")
    sandbox.cmd("touch mydir/bbb")
    sandbox.cmd("touch mydir/ccc")
    sandbox.cmd("touch mydir2/111")
    sandbox.cmd("touch mydir2/222")
    sandbox.cmd("touch mydir2/333")
    return sandbox.run()


def test_multiple_dirs_2():
    sandbox = Sandbox("test_multiple_dirs_2", "mydir mydir2")
    sandbox.cmd("mkdir mydir mydir2 && touch {} && touch {}".format(
        " ".join(["mydir/file" + str(n) for n in range(10, 21)]),
        " ".join(["mydir2/file" + str(n) for n in range(30, 41)]),
    ))
    return sandbox.run()


def test_multiple_dirs_3():
    sandbox = Sandbox("test_multiple_dirs_3", "{}".format(" ".join(["mydir" + str(n) for n in range(1, 8)])))
    sandbox.cmd("mkdir {} && touch {}".format(
        " ".join(["mydir" + str(n) for n in range(1, 8)]),
        " ".join(["mydir" + str(n) + "/file" + str(n2) for n2 in range(1, 12) for n in range(1, 8)])
    ))
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
