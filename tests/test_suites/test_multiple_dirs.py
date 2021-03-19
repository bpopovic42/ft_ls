from testing_utils.run_test import run_test
from testing_utils.sandbox import Sandbox


def test_multiple_dirs_1():
    sandbox = Sandbox("test_multiple_dirs_1")
    sandbox.run("mkdir mydir mydir2 && touch mydir/{aaa,bbb,ccc} && touch mydir2/{111,222,333}")
    return run_test(sandbox, "mydir mydir2")


def test_multiple_dirs_2():
    sandbox = Sandbox("test_multiple_dirs_2")
    sandbox.run("mkdir mydir mydir2 && touch mydir/file{10..20} && touch mydir2/file{30..40}")
    return run_test(sandbox, "mydir mydir2")


def test_multiple_dirs_3():
    sandbox = Sandbox("test_multiple_dirs_3")
    sandbox.run("mkdir mydir{1..7} && touch mydir{1..7}/file{1..11}")
    return run_test(sandbox, "mydir{1..7}")


def test_multiple_dirs_4():
    sandbox = Sandbox("test_multiple_dirs_4")
    sandbox.run("mkdir mydir && touch mydir/a")
    return run_test(sandbox, "mydir")


def run_test_multiple_dirs():
    test_multiple_dirs_1()
    test_multiple_dirs_2()
    test_multiple_dirs_3()
    test_multiple_dirs_4()
