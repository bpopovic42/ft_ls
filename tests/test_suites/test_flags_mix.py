from testing_utils.sandbox import Sandbox


def test_flags_mix_1():
    sandbox = Sandbox("test_flags_mix_1", "-lR .")
    sandbox.cmd("mkdir {} {}".format(" ".join(["dir" + str(n) for n in range(0, 5)]),
                                     " ".join([".hdir" + str(n) for n in range(0, 5)])))
    sandbox.cmd("touch {} {}".format(" ".join(["dir1/file" + str(n) for n in range(0, 5)]),
                                     " ".join(["dir1/.hfile" + str(n) for n in range(0, 5)])))
    sandbox.cmd("touch {} {}".format(" ".join([".hdir1/file" + str(n) for n in range(0, 5)]),
                                     " ".join([".hdir1/.hfile" + str(n) for n in range(0, 5)])))
    sandbox.cmd("touch a && ln -s a symlink")
    return sandbox.run()


def run_test_flags_mix():
    test_flags_mix_1()
