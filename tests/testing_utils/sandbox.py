import os
import shutil
from testing_utils.utils import make_new_unique_path

SANDBOXES_PATH = os.path.join(os.path.dirname(__file__), "../sandbox")


class Sandbox:
    def __init__(self, name):
        self.path = make_new_unique_path(SANDBOXES_PATH)
        self.name = name

    def run(self, command):
        current_dir = os.getcwd()
        os.chdir(self.path)
        os.system(command)
        os.chdir(current_dir)

    def clean(self):
        shutil.rmtree(self.path)
