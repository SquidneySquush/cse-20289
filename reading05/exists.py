#!/usr/bin/env python3

import os

def exists(fname):
	path = os.path.abspath(fname)
	if os.path.exists(path):
		print(fname+"exists!")
	else:
		return(0)
	return(1)

