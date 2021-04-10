from testing_utils.sandbox import Sandbox


def test_l_flag_1():
    sandbox = Sandbox("test_l_flag_1", "-l")
    sandbox.cmd("touch a b c && echo 'coucou' > a &&  echo 'hello world' > b")
    sandbox.cmd("mkdir 111 222 333 444 && touch 111/{a,b,c} && echo 'eat pizza' > 111/a")
    return sandbox.run()


def test_l_flag_2():
    sandbox = Sandbox("test_l_flag_2", "-l")
    sandbox.cmd("touch .a")
    sandbox.cmd("dd count=14450 if=/dev/zero of=.a  >/dev/null 2>&1")
    sandbox.cmd("ln -s .a b")
    return sandbox.run()


def test_l_flag_3():
    sandbox = Sandbox("test_l_flag_3", "-la dir")
    sandbox.cmd("mkdir -p dir/.hdir")
    sandbox.cmd("touch dir/.hdir/file")
    return sandbox.run()


def test_l_flag_4():
    sandbox = Sandbox("test_l_flag_4", "-l dir")
    sandbox.cmd("mkdir -p dir")
    sandbox.cmd("touch dir/.file touch dir/visible")
    sandbox.cmd("ln dir/.file sym0")
    sandbox.cmd("ln dir/.file sym1")
    sandbox.cmd("ln dir/.file sym2")
    sandbox.cmd("ln dir/.file sym3")
    sandbox.cmd("ln dir/.file sym4")
    sandbox.cmd("ln dir/.file sym5")
    sandbox.cmd("ln dir/.file sym6")
    sandbox.cmd("ln dir/.file sym7")
    sandbox.cmd("ln dir/.file sym8")
    sandbox.cmd("ln dir/.file sym9")
    sandbox.cmd("ln dir/.file sym10")
    return sandbox.run()


def test_l_flag_5():
    sandbox = Sandbox("test_l_flag_5", "-lt")
    sandbox.cmd("touch -t 999912312359 future")
    return sandbox.run()


def test_l_flag_padding():
    sandbox = Sandbox("test_l_flag_padding", "-l")
    sandbox.cmd("mkdir .test_dir")
    return sandbox.run()


def get_tests_l_flag():
    return (
        test_l_flag_1,
        test_l_flag_2,
        test_l_flag_3,
        test_l_flag_4,
        test_l_flag_5,
        test_l_flag_padding
    )
