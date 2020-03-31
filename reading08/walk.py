#!/usr/bin/env python3

import os
import sys

# TODO: Determine which directory to walk from command line argument
try:
    directory = sys.argv[1]
except IndexError:
    directory = os.getcwd()

# TODO: Walk specified directory in sorted order and print out each entry's
# file name

dir_content = sorted(os.listdir(directory))

for item in dir_content:
    print(item)
