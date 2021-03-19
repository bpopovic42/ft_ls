import os
from datetime import datetime
from uuid import uuid4


def make_new_unique_path(basepath):
    eventid = datetime.now().strftime('%Y%m-%d%H-%M%S-') + str(uuid4())
    unique_path = basepath + "/" + eventid
    os.mkdir(unique_path)
    return unique_path


def write_process_stdout_to_file(process, filepath):
    file = open(filepath, "w+")
    file.write(process.stdout.decode("utf-8"))
    file.close()
