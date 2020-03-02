#!/usr/bin/env python3

import sys

result = filter ( lambda x: not int(x) % 2, map(str.strip, sys.stdin))

print(' '.join(result))
