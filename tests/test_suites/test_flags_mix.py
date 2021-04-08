from testing_utils.sandbox import Sandbox


def test_flags_mix_1():
    sandbox = Sandbox("test_flags_mix_1", "-lR .")
    sandbox.cmd("mkdir {} {}".format(" ".join(["dir" + str(n) for n in range(1, 5)]),
                                     " ".join([".hdir" + str(n) for n in range(1, 5)])))
    sandbox.cmd("touch {} {}".format(" ".join(["dir1/file" + str(n) for n in range(1, 5)]),
                                     " ".join(["dir1/.hfile" + str(n) for n in range(1, 5)])))
    sandbox.cmd("touch {} {}".format(" ".join([".hdir1/file" + str(n) for n in range(1, 5)]),
                                     " ".join([".hdir1/.hfile" + str(n) for n in range(1, 5)])))
    sandbox.cmd("touch a && ln -s a symlink")
    return sandbox.run()


def get_tests_flags_mix():
    return [
        test_flags_mix_1
    ]
