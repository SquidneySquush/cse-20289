#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [flags]

    -c      Prefix lines by the number of occurrences
    -d      Only print duplicate lines
    -i      Ignore differences in case when comparing, prints out full line in lowercase
    -u      Only print unique lines

By default, {progname} prints one of each type of line.''')
    sys.exit(status)

def count_frequencies(stream=sys.stdin, ignore_case=False):
    ''' Count the line frequencies from the data in the specified stream while
    ignoring case if specified. '''
    counts = {}
    for line in stream:
        line = line.rstrip()
        if ignore_case:
            line = line.lower()
        counts[line] = counts.get(line, 0) + 1
    return counts

def print_lines(frequencies, occurrences=False, duplicates=False, unique_only=False):
    ''' Display line information based on specified parameters:

    - occurrences:  if True, then prefix lines with number of occurrences
    - duplicates:   if True, then only print duplicate lines
    - unique_only:  if True, then only print unique lines
    '''
    frequency = frequencies
    for line, value in frequency.items():
        if occurrences:
            print(f'{value:>7} {line}')
        elif duplicates:
            if frequency[line] > 1:
                print(f'{line}'.format(line))
        elif unique_only:
            if frequency[line] == 1:
                print(f'{line}'.format(line))
        else:
            print(f'{line}')


def main():
    ''' Process command line arguments, count frequencies from standard input,
    and then print lines. '''
    arguments = sys.argv[1:]
    occurrences = False
    duplicates = False
    ignore_case = False
    unique_only = False

    while arguments and arguments[0].startswith('-'): ## checks for -h flag
        argument = arguments.pop(0)
        if argument == '-c':
            occurrences = 'True'
            continue
        elif argument == '-d':
            duplicates = 'True'
            continue
        elif argument == '-i':
            ignore_case = 'True'
            continue
        elif argument == '-u':
            unique_only = 'True'
            continue
        elif argument == '-h':
            usage(0)
        else:
            usage(1)

    stream=sys.stdin

    counts= count_frequencies(stream, ignore_case)

    print_lines(counts,occurrences, duplicates, unique_only)

    sys.exit(0)

# Main Execution

if __name__ == '__main__':
    main()

    ## posibly open sys.stdin?   change to use collect counter
     ### enumerate?
