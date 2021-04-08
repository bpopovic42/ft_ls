import os
import shutil
import subprocess

from testing_utils.utils import get_new_folder, append_to_file, get_new_file
from testing_utils.globals import SANDBOXES_DIR, FT_LS_PATH, LS_PATH, COLOR_GREEN, COLOR_RED, COLOR_END

SHOULD_PRINT_RESULTS = False
SHOULD_KEEP_ALL_RESULTS = False


def sanitize_stderr(stderr):
    remove_program_name = (
        lambda _stderr: "\n".join([line.split(": ", 1)[1] for line in _stderr.split("\n") if ": " in line])
    )
    if not stderr:
        return stderr
    else:
        return remove_program_name(stderr)


def get_test_results(ls, ft_ls):
    test_results = TestResult()
    test_results.crash = ft_ls.returncode < 0
    test_results.returncode_matches = ls.returncode == ft_ls.returncode
    test_results.stdout_matches = ls.stdout.decode("utf-8") == ft_ls.stdout.decode("utf-8")
    test_results.stderr_matches = (
            sanitize_stderr(ls.stderr.decode("utf-8")) == sanitize_stderr(ft_ls.stderr.decode("utf-8"))
    )
    test_results.success = (
            test_results.returncode_matches and
            test_results.stdout_matches and
            test_results.stderr_matches and
            not test_results.crash

    )
    return test_results


class TestResult:
    def __init__(self):
        self.stdout_matches = False
        self.stderr_matches = False
        self.returncode_matches = False
        self.success = False
        self.crash = False


class Sandbox:
    def __init__(self, name, arguments, provided_working_dir=None, print_results=SHOULD_PRINT_RESULTS):
        self.path = get_new_folder(SANDBOXES_DIR, name)
        self.test_dir_path = get_new_folder(self.path, "test_dir") if not provided_working_dir else None
        self.working_dir = self.test_dir_path if not provided_working_dir else provided_working_dir
        self.results_dir_path = get_new_folder(self.path, "results")
        self.info_file_path = get_new_file(self.path, "info")
        self.ls_output_file_path = get_new_file(self.results_dir_path, "ls_output")
        self.ft_ls_output_file_path = get_new_file(self.results_dir_path, "ft_ls_output")
        self.print_results = print_results
        self.name = name
        self.arguments = arguments.split(" ") if len(arguments) > 0 else []
        self.ls = None
        self.ft_ls = None
        self.test_results = TestResult()

    def __record_stderr(self):
        stderr_header = "# STDERR :"
        append_to_file(self.ls_output_file_path, stderr_header)
        append_to_file(self.ls_output_file_path, sanitize_stderr(self.ls.stderr.decode("utf-8")))
        append_to_file(self.ft_ls_output_file_path, stderr_header)
        append_to_file(self.ft_ls_output_file_path, sanitize_stderr(self.ft_ls.stderr.decode("utf-8")))

    def __record_stdout(self):
        stdout_header = "# STDOUT :"
        append_to_file(self.ls_output_file_path, stdout_header)
        append_to_file(self.ls_output_file_path, self.ls.stdout.decode("utf-8"))
        append_to_file(self.ft_ls_output_file_path, stdout_header)
        append_to_file(self.ft_ls_output_file_path, self.ft_ls.stdout.decode("utf-8"))

    def __record_returncodes(self):
        return_code_header = "# RETURN CODE :"
        append_to_file(self.ls_output_file_path, return_code_header)
        append_to_file(self.ls_output_file_path, self.ls.returncode)
        append_to_file(self.ft_ls_output_file_path, return_code_header)
        append_to_file(self.ft_ls_output_file_path, self.ft_ls.returncode)

    def __record_test_info(self):
        append_to_file(self.info_file_path, "Arguments :\t\t " + " ".join(self.arguments))
        for (output_name, output_matches) in [
            ("Returncode :\t\t ", self.test_results.returncode_matches),
            ("Stdout :\t\t ", self.test_results.stdout_matches),
            ("Stderr :\t\t ", self.test_results.stderr_matches)
        ]:
            append_to_file(
                self.info_file_path,
                (
                        output_name + (
                    (COLOR_GREEN + "MATCHES" + COLOR_END)
                    if output_matches else
                    (COLOR_RED + "DIFFERS" + COLOR_END)
                )
                )
            )

    def __record_test_results(self):
        self.__record_test_info()
        self.__record_returncodes()
        self.__record_stdout()
        self.__record_stderr()

    def __print_test_results(self):
        if self.print_results and (not self.test_results.stdout_matches or not self.test_results.stderr_matches):
            os.system("diff -u " + self.ls_output_file_path + " " + self.ft_ls_output_file_path + " | ydiff -s -p cat")

    def __process_test_results(self):
        if self.test_results.success:
            print("{}: ".format(self.name).ljust(40, " ") + COLOR_GREEN + "PASSED" + COLOR_END)
        else:
            if self.test_results.crash:
                print("{}: ".format(self.name).ljust(40, " ") + COLOR_RED + "CRASH" + COLOR_END)
            else:
                print("{}: ".format(self.name).ljust(40, " ") + COLOR_RED + "FAILED " + COLOR_END)
            self.__record_test_results()
            self.__print_test_results()

    def run(self):
        self.ls = subprocess.run([LS_PATH] + self.arguments, cwd=self.working_dir, capture_output=True)
        self.ft_ls = subprocess.run([FT_LS_PATH] + self.arguments, cwd=self.working_dir, capture_output=True)
        self.test_results = get_test_results(self.ls, self.ft_ls)
        self.__process_test_results()
        self.clean()
        return self.test_results.success

    def cmd(self, command):
        current_dir = os.getcwd()
        os.chdir(self.test_dir_path)
        os.system(command)
        os.chdir(current_dir)

    def clean(self):
        if self.test_results.success and not SHOULD_KEEP_ALL_RESULTS:
            try:
                shutil.rmtree(self.path)
            except PermissionError:
                self.cmd("chmod -R 755 {}".format(self.path))
                shutil.rmtree(self.path)
