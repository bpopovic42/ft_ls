import os

from testing_utils import sandbox
from testing_utils.sandbox import Sandbox


def test_from_cli(arguments):
    sandbox.Sandbox.set_printing(True)
    cli_sandbox = Sandbox("cli_test", arguments, provided_working_dir=os.getcwd())
    cli_sandbox.run()
