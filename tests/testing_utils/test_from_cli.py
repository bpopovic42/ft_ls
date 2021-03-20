import os

from testing_utils.sandbox import Sandbox


def test_from_cli(arguments):
    sandbox = Sandbox("cli_test", arguments, provided_working_dir=os.getcwd(), print_results=True)
    sandbox.run()
