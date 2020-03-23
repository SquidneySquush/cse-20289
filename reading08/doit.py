#!/usr/bin/env python3

import os
import sys

def doit(argv):
    try:
        pid = os.fork()    # TODO: Create new process
    except OSError:
        return 1

    if pid == 0:      # Child
        try:
            os.execvp(argv[0], argv)      # TODO: Execute new code in current process
        except (IndexError, OSError):
            sys.exit(2)      # TODO: Exit with status 2
    else:             # Parent
        pid, status = os.wait()          # TODO: Wait for child process
        return os.WEXITSTATUS(status)   # TODO: Return exit status of child process

if __name__ == '__main__':
    status = doit(sys.argv[1:])
    sys.exit(status)
