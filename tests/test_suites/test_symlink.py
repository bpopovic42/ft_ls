from testing_utils.sandbox import Sandbox


def test_symlink_1():
    sandbox = Sandbox("test_symlink_1", "symdir")
    sandbox.cmd("mkdir mydir && ln -s mydir symdir && touch {}".format(
        " ".join(["mydir/file" + str(n) for n in range(1, 6)])
    ))
    return sandbox.run()


def test_symlink_2():
    sandbox = Sandbox("test_symlink_2", "b")
    sandbox.cmd("touch a")
    sandbox.cmd("ln -s a b")
    return sandbox.run()


def test_symlink_3():
    sandbox = Sandbox("test_symlink_3", "b")
    sandbox.cmd("mkdir a")
    sandbox.cmd("ln -s a b")
    sandbox.cmd("rm -rf a")
    return sandbox.run()


def test_symlink_4():
    sandbox = Sandbox("test_symlink_4", "-l b")
    sandbox.cmd("mkdir a")
    sandbox.cmd("ln -s a b")
    sandbox.cmd("rm -rf a")
    return sandbox.run()


def run_test_symlink():
    test_symlink_1()
    test_symlink_2()
    test_symlink_3()
    test_symlink_4()
