#!/usr/bin/env python3

import os
import signal
import sys
import time

# global
Stop        = False
ChildPid    = 0
ChildStatus = None

# Functions

def usage(status=0):
    ''' Display usage message for program and exit with specified status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [options] command...
Options:
    -t SECONDS  Timeout duration before killing command (default is 10)
''')
    sys.exit(status)

def error(message, status=1):
    ''' Display error message and exit with specified status. '''
    print(message, file=sys.stderr)
    sys.exit(status)

def alarm_handler(signum, frame):
    ''' Alarm handler that raises InterruptedError '''
    global Stop, ChildPid#, ChildStatus  # set globals so they can be edited

    Stop = True

    ChildPid = os.getpid()
    os.kill(ChildPid, signal.SIGKILL)

    #pid, status = os.wait()
    #return status
    status = 9#signal.SIGKILL
    return status

    raise InterruptedError (status)


def timeit(argv, timeout):
    ''' Run command specified by argv for at most timeout seconds.

    - After forking, the child executes the specified command.

    - After forking, the parent does the following:
        - Registers a handler for SIGALRM
        - Set alarm for specified timeout
        - Waits for child process
        - If wait is interrupted, kills the child process and wait again
        - Prints total elapsed time
        - Exits with the status of the child process
    '''
    #global pid
    try:
        pid = os.fork()    # TODO: Create new process
        start = time.time()                # start timer
    except OSError:
        print('fork failed', file=sys.stderr)
        sys.exit(3)

    if pid == 0:      # Child
        try:
            #print(argv)
            os.execvp(argv[0], argv)      # TODO: Execute new code in current process
        except (IndexError, OSError):
            if len(argv) < 1:
                usage(1)
            error(argv[0], status=1)
            #sys.exit(3)

    else:             # Parent
        try:
            signal.signal(signal.SIGALRM, alarm_handler) # TODO:If recieves signal run alam_handler
            signal.alarm(timeout)           #set alarm for time in timeout

            while not ChildPid:
                #time.sleep(timeout)
                try:
                    pid, status = os.wait()
                    seconds = time.time() # end elapsed time from start of function
                    finalTime = (seconds-start)
                    print('Time Elapsed: ', finalTime)
                except ChildProcessError:
                    break
            seconds = time.time() # end elapsed time from start of function
            finalTime = (seconds-start)
            print('Time Elapsed: ', finalTime)
        except:
            if os.WIFEXITED(status):
                print(f'Exit Status: {os.WEXITSTATUS(status)}')

            else:
                print(f'Termination Status: {os.WTREMSIG(status)}')
                #return False


def main():
    ''' Parse command line options and then execute timeit with specified
    command and timeout. '''
    #timeout = 10
    timeToggle = False
    arguments = sys.argv[1:]

    #if len(arguments) == 0:
    #    usage(1)
    while len(arguments) and arguments[0].startswith('-'): ## checks for -h flag
        argument = arguments.pop(0)
        if argument == '-t':
            timeToggle = True
        if argument == '-h':
            usage(0)
        else:
            break

    if timeToggle:
        timeout = arguments.pop(0)
        timeout = int(timeout)
    else:
        timeout = 10

    #if len(arguments) <= 1:
    #    usage(1)

    timeit(arguments, timeout)


# Main Execution

if __name__ == '__main__':
    main()
