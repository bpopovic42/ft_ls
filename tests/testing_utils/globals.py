import os
import subprocess as sb

LS_PATH = sb.check_output(["which", "ls"]).decode("utf-8").replace("\n", "")
FT_LS_PATH = os.path.join(os.path.dirname(__file__), "../../ft_ls/ft_ls")
RESULTS_DIR = os.path.join(os.path.dirname(__file__), "../results")
SANDBOXES_DIR = os.path.join(os.path.dirname(__file__), "../sandbox")
