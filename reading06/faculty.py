#!/usr/bin/env python3

import collections
import re
import requests

# Constants

URL = 'https://cse.nd.edu/people/faculty'

# Initialize a dictionary with integer values
counts = collections.defaultdict(int)

# TODO: Make a HTTP request to URL
response = requests.get(URL)

# TODO: Access text from response object
data = response.text

# TODO: Compile regular expression to extract degrees and years of each faculty
# member
regex = re.compile(r'.*<p>.*[Ph\.D {3,5}| M\.S]{3,5}.*(\d{4}).*</p>.*')

# TODO: Search through data using compiled regular expression and count up all
# the faculty members per year.
findyear = re.findall(regex, data)

for year in findyear:
    counts[year] = counts.get(year, 0) + 1

# TODO: Sort items in counts by key in reverse order
items = {}
items = sorted(counts.items(), key=lambda p: p[0], reverse=True)

# Sort items by value in reverse order and display counts and years
for year, count in sorted(items, key=lambda p: p[1], reverse=True):
    print(f'{count:>7} {year}')
