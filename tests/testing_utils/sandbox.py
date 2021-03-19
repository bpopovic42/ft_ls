import os
import shutil
from testing_utils.utils import get_new_folder
from testing_utils.globals import SANDBOXES_DIR


class Sandbox:
    def __init__(self, name):
        self.path = get_new_folder(SANDBOXES_DIR, name)
        self.name = name

    def run(self, command):
        current_dir = os.getcwd()
        os.chdir(self.path)
        os.system(command)
        os.chdir(current_dir)

    def clean(self):
        try:
            shutil.rmtree(self.path)
        except PermissionError:
            self.run("chmod -R 755 {}".format(self.path))
            shutil.rmtree(self.path)
