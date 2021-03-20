from testing_utils.sandbox import Sandbox


def test_l_flag_1():
    sandbox = Sandbox("test_l_flag_1", "-l")
    sandbox.cmd("touch a b c && echo 'coucou' > a &&  echo 'hello world' > b")
    sandbox.cmd("mkdir 111 222 333 444 && touch 111/{a,b,c} && echo 'eat pizza' > 111/a")
    return sandbox.run()


def test_l_flag_2():
    sandbox = Sandbox("test_l_flag_2", "-l")
    sandbox.cmd("touch file && xattr -w theAnswerIs42 whatever_you_want file")
    return sandbox.run()


def test_l_flag_padding():
    sandbox = Sandbox("test_l_flag_padding", "-l")
    sandbox.cmd("mkdir .test_dir")
    return sandbox.run()


def run_test_l_flag():
    test_l_flag_1()
    test_l_flag_2()
    test_l_flag_padding()
