#!/usr/bin/env python3

import requests

# Constants

URL = 'http://catalog.cse.nd.edu:9097/query.json'
#headers  = {'user-agent': __file__}

# TODO: Make a HTTP request to URL
response = requests.get(URL) #, headers=headers)

# TODO: Access json representation from response object
data     = response.json()

# TODO: Display all machine names with type "wq_factory"
for row in data:
    if row['type'] == 'wq_factory':
        print(row['name'])
