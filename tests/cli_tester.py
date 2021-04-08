#!/usr/bin/env python3.8

import sys

from testing_utils.test_from_cli import test_from_cli
from testing_utils.utils import clean_existing_tests

if __name__ == '__main__':
    clean_existing_tests()
    test_from_cli(" ".join(sys.argv[1:]))
