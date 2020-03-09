#!/usr/bin/env python3

import sys

result = [ line.strip() for line in sys.stdin if not int(line) % 2 ]

print(' '.join(result))

