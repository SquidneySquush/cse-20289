#!/usr/bin/env python3

import os
import sys

# Globals

OPERATORS = {'+', '-', '*', '/'}

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname}

By default, {progname} will process expressions from standard input.''')

    sys.exit(status)

def error(message):
    ''' Display error message and exit with error. '''
    print(message, file=sys.stderr)
    sys.exit(1)

def evaluate_operation(operation, operand1, operand2):
    ''' Return the result of evaluating the operation with operand1 and
    operand2.

    >>> evaluate_operation('+', 4, 2)
    6

    >>> evaluate_operation('-', 4, 2)
    2

    >>> evaluate_operation('*', 4, 2)
    8

    >>> evaluate_operation('/', 4, 2)
    2.0
    '''

    if operation == '+':
        return operand1 + operand2
    if operation == '-':
        return operand1 - operand2
    if operation == '*':
        return operand1 * operand2
    if operation == '/':
        try:
            return operand1 / operand2
        except ZeroDivisionError:
            sys.exit(1)


def evaluate_expression(expression):
    ''' Return the result of evaluating the RPN expression.

    >>> evaluate_expression('4 2 +')
    6.0

    >>> evaluate_expression('4 2 -')
    2.0

    >>> evaluate_expression('4 2 *')
    8.0

    >>> evaluate_expression('4 2 /')
    2.0

    >>> evaluate_expression('4 +')
    Traceback (most recent call last):
    ...
    SystemExit: 1

    >>> evaluate_expression('a b +')
    Traceback (most recent call last):
    ...
    SystemExit: 1
    '''

    stack = []

    for token in expression.split():
        if token in OPERATORS:
            try:
                operand2 = stack.pop(-1)
                operand1 = stack.pop(-1)
                operation = token
                result = evaluate_operation(operation, operand1, operand2)
            except IndexError:
                sys.exit(1)
        else:
            try:
                result = float(token)
            except ValueError:
                sys.exit(1)
        stack.append(result)
    print(result)


def main():
    ''' Parse command line arguments and process expressions from standard
    input. '''
    arguments = sys.argv[1:]
    while len(arguments) and arguments[0].startswith('-'): ## checks for -h flag
        argument = arguments.pop(0)
        if argument == 'h':
            usage(0)
        else:
            usage(1)

    for line in sys.stdin:
        line = line.rstrip()
        evaluate_expression(line)

    sys.exit(0)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
