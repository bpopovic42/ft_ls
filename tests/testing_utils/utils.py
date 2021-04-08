import os
import shutil

from testing_utils import sandbox
from testing_utils.globals import SANDBOXES_DIR


def get_new_folder(basepath, folder_name):
    new_folder_path = basepath + "/" + folder_name
    os.mkdir(new_folder_path)
    return new_folder_path


def get_new_file(basepath, file_name):
    new_file_path = basepath + "/" + file_name
    os.system("touch {}".format(new_file_path))
    return new_file_path


def append_to_file(filepath, to_append):
    file = open(filepath, "a")
    print(str(to_append), file=file)
    file.close()


def clean_existing_tests():
    if os.path.exists(SANDBOXES_DIR):
        try:
            shutil.rmtree(SANDBOXES_DIR)
        except PermissionError:
            os.system("chmod -R 755 {}".format(SANDBOXES_DIR))
            shutil.rmtree(SANDBOXES_DIR)
    os.mkdir(SANDBOXES_DIR)


def process_cli_flags(cli_args):
    for arg in cli_args:
        if len(arg) > 0 and arg[0] == "-":
            if "p" in arg:
                sandbox.Sandbox.set_printing(True)
            if "s" in arg:
                sandbox.Sandbox.set_record(True)
