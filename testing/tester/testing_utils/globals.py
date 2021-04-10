import os
import subprocess as sb

LS_PATH = sb.check_output(["which", "ls"]).decode("utf-8").replace("\n", "")
FT_LS_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../ft_ls/ft_ls"))
SANDBOXES_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "../sandbox"))
COLOR_GREEN = '\033[92m'
COLOR_RED = '\033[91m'
COLOR_END = '\033[0m'
