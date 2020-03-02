#!/usr/bin/env python3

import sys

def evens(stream):
	for line in sys.stdin:
		if not int(line) % 2:
			yield line.strip()

result = evens(sys.stdin)
print(' '.join(result))
