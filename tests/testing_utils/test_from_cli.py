import subprocess as sb
from testing_utils.globals import LS_PATH, FT_LS_PATH
from testing_utils.run_test import compare

def test_from_cli(arguments):
    original_ls = sb.run([LS_PATH] + arguments, capture_output=True)
    ft_ls = sb.run([FT_LS_PATH] + arguments, capture_output=True)
    compare(" ".join(arguments), original_ls, ft_ls)
