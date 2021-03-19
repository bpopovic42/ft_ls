import os
import shutil

from testing_utils.globals import RESULTS_DIR, SANDBOXES_DIR


def get_new_folder(basepath, folder_name):
    unique_path = basepath + "/" + folder_name
    os.mkdir(unique_path)
    return unique_path


def write_process_stdout_to_file(process, filepath):
    file = open(filepath, "w+")
    file.write(process.stdout.decode("utf-8"))
    file.close()


def clean_existing_results():
    if os.path.exists(RESULTS_DIR):
        shutil.rmtree(RESULTS_DIR)
    if os.path.exists(SANDBOXES_DIR):
        shutil.rmtree(SANDBOXES_DIR)
    os.mkdir(RESULTS_DIR)
    os.mkdir(SANDBOXES_DIR)
