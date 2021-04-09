from testing_utils.sandbox import Sandbox


def test_parsing_ending_slash():
    sandbox = Sandbox("test_parsing_ending_slash", "-lR dir_01/")
    sandbox.cmd("mkdir dir_01 && mkdir dir_01/dir_02 && mkdir dir_01/dir_03")
    sandbox.cmd("touch dir_01/file_01 dir_01/file_02 dir_01/dir_02/file_03 dir_01/dir_03/file_04")
    return sandbox.run()


def test_parsing_ending_multi_slash():
    sandbox = Sandbox("test_parsing_ending_multi_slash", "-lR dir_01////")
    sandbox.cmd("mkdir dir_01 && mkdir dir_01/dir_02 && mkdir dir_01/dir_03")
    sandbox.cmd("touch dir_01/file_01 dir_01/file_02 dir_01/dir_02/file_03 dir_01/dir_03/file_04")
    return sandbox.run()


def test_parsing_repeated_slashes():
    sandbox = Sandbox("test_parsing_repeated_slashes", "-lR dir_01////dir_02///dir_03///")
    sandbox.cmd("mkdir dir_01 && mkdir dir_01/dir_02 && mkdir dir_01/dir_02/dir_03 && mkdir dir_01/dir_02/dir_03/dir_04")
    sandbox.cmd("touch dir_01/dir_02/dir_03/file_03 dir_01/dir_02/dir_03/file_04 dir_01/dir_02/dir_03/dir_04/file_05")
    return sandbox.run()


def get_tests_parsing():
    return [
        test_parsing_ending_slash,
        test_parsing_ending_multi_slash,
        test_parsing_repeated_slashes
    ]
