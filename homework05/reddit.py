#!/usr/bin/env python3

import os
import sys
import re
import pprint
import requests

# Constants

ISGD_URL = 'http://is.gd/create.php'
REDDIT_URL = 'https://www.reddit.com/r/'
JSON_TAG = '/.json'

# Functions

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    print('''Usage: {} [options] URL_OR_SUBREDDIT

    -s          Shorten URLs using (default: False)
    -n LIMIT    Number of articles to display (default: 10)
    -o ORDERBY  Field to sort articles by (default: score)
    -t TITLELEN Truncate title to specified length (default: 60)
    '''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

def load_reddit_data(url):
    ''' Load reddit data from specified URL into dictionary

    >>> len(load_reddit_data('https://reddit.com/r/nba/.json'))
    27

    >>> load_reddit_data('linux')[0]['data']['subreddit']
    'linux'
    '''
    # TODO: Verify url parameter (if it starts with http, then use it,
    # otherwise assume it is just a subreddit).
    ## I think the length of the first doc test should be 26 not 27
    headers  = {'user-agent': 'reddit-{}'.format(os.environ.get('USER', 'cse-20289-sp20'))}
    checkUrl = re.findall('http(.*)',str(url))

    if checkUrl:
        response = requests.get(url, headers=headers)
    else:
        url = ('{}{}{}'.format(REDDIT_URL, url, JSON_TAG))
        response = requests.get(url, headers=headers)

    return (response.json()['data']['children'])


def shorten_url(url):
    ''' Shorten URL using is.gd service

    >>> shorten_url('https://reddit.com/r/aoe2')
    'https://is.gd/dL5bBZ'

    >>> shorten_url('https://cse.nd.edu')
    'https://is.gd/3gwUc8'
    '''
    # TODO: Make request to is.gd service to generate shortened url.
    shortUrl = requests.get(ISGD_URL, params={'format': 'json', 'url': url})

    return(shortUrl.json()['shorturl'])

def print_reddit_data(data, limit, orderby, titlelen, shorten):
    ''' Dump reddit data based on specified attributes '''
    # TODO: Sort articles stored in data list by the orderby key, and then
    # print out each article's index, title, score, and url using the following
    # format:
    #
    #   print(f'{index:4}.\t{title} (Score: {score})\n\t{url}')
    #
    # Note: Trim or modify the output based on the keyword arguments to the function.

    reverse = orderby == 'score'
    articles = sorted(data, key=lambda i: i['data'][orderby], reverse = reverse)
    articles = articles[:int(limit)]

    for index, article in enumerate(articles,0):
        title = article['data']['title']
        score = article['data']['score']
        url   = article['data']['url']
        if shorten == True:
            url = shorten_url(url)
        if index:
            print()

        print(f'{(index+1):4}.\t{title[:int(titlelen)]} (Score: {score})\n\t{url}')

def main():
    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    url       = None
    limit     = 10
    orderby   = 'score'
    titlelen  = 60
    shorten   = False

    #print(len(arguments))
    if len(arguments) == 0:
        print('fail')
        usage(1)

    while len(arguments) and arguments[0].startswith('-'): ## checks for -h flag
        argument = arguments.pop(0)
        if argument == '-s':
            shorten = True
            continue
        elif argument == '-n':
            limit = arguments.pop(0)
            continue
        elif argument == '-o':
            orderby = arguments.pop(0)
            continue
        elif argument == '-t':
            titlelen = arguments.pop(0)
            continue
        elif argument == '-h':
            usage(0)
        else:
            usage(1)

    url = arguments[0]

    # TODO: Load data from url and then print the data
    data = {}
    data = load_reddit_data(url)

    print_reddit_data(data, limit, orderby, titlelen, shorten)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
