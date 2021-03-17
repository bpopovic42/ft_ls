import os
from datetime import datetime
from uuid import uuid4


def make_new_unique_path(basepath):
    eventid = datetime.now().strftime('%Y%m-%d%H-%M%S-') + str(uuid4())
    unique_path = basepath + "/" + eventid
    os.mkdir(unique_path)
    return unique_path
