#!/usr/bin/env python3

import os
import sys

# TODO: Determine which directory to walk from command line argument
if len(sys.argv[1]) >= 1:
    directory = sys.argv[1]
else:
    directory = os.getcwd()

# TODO: Walk specified directory in sorted order and print out each entry's
# file name

for dirpath, dirnames, files in os.walk(directory):
    print(f'{dirpath}')
    for file_name in files:
        print(file_name)
