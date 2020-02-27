#!/usr/bin/env python3

import csv
# Constants

PATH = '/etc/passwd'

# TODO: Loop through ':' delimited data in PATH and extract the fifth field
# ()
file = open(PATH)
reader = csv.reader(file, ['0','1','2','3','descript','5'], delimiter = ':')

# TODO: Print user descriptions in sorted order
descriptions = []
for row in reader:
    if len(row[4]) > 0:
        descriptions.append(row[4])

#list = sorted(descriptions, key=lambda p: p['descript'], reverse=True)
list = sorted(descriptions)

for line in list:
    print(line)
