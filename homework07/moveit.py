#!/usr/bin/env python3

import atexit
import os
import sys
import tempfile

# Functions

def usage(status=0):
    ''' Display usage message for program and exit with specified status. '''
    print(f'Usage: {os.path.basename(sys.argv[0])} files...')
    sys.exit(status)

def save_files(files):
    ''' Save list of files to a temporary file and return the name of the
    temporary file. '''
    with tempfile.NamedTemporaryFile(delete=False) as tf:
        for file in files:
            tf.write(file.encode()+'\n'.encode())
    return tf.name

def edit_files(path):
    ''' Fork a child process to edit the file specified by path using the user's
    default EDITOR (use "vim" if not set).  Parent waits for child process and
    returns whether or not the child was successful. '''
    try:
        editor = os.environ.get('EDITOR','vim')  #Grabs ENV var
        pid = os.fork()    # TODO: Create new process
    except OSError:
        print('fork failed', file=sys.stderr)
        sys.exit(3)

    if pid == 0:      # Child
        try:
            os.execlp(editor, 'editor', path)      # TODO: Execute new code in current process
        except (IndexError, OSError):
            return False
            #sys.exit(3)   # TODO: Exit with status 2

    else:             # Parent
        pid, status = os.wait()          # TODO: Wait for child process
        if os.WIFEXITED(status):
            print(f'Exit Status: {os.WEXITSTATUS(status)}')
        else:
            print(f'Termination Status: {os.WTREMSIG(status)}')
            return False


def move_files(files, path):
    ''' For each file in files and the corresponding information from the file
    specified by path, rename the original source file to the new target path
    (if the names are different).  Return whether or not all files were
    successfully renamed. '''
    zip_file = zip(files, open(path).read().split())
    for old_file, new_file in zip_file:
        if not new_file == old_file:
            try:
                os.rename(old_file, new_file)
            except:
                return False
        else:
            return False


def main():
    ''' Parse command line arguments, save arguments to temporary file, allow
    the user to edit the temporary file, move the files, and remove the
    temporary file. '''
    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    if len(arguments) == 0:
        usage(0)
    while len(arguments) and arguments[0].startswith('-'): ## checks for -h flag
        argument = arguments.pop(0)
        if argument == 'h':
            usage(0)
        else:
            usage(1)

    # TODO: Save files (arguments)
    path = save_files(arguments)

    # TODO: Register unlink to cleanup temporary file
    atexit.register(os.unlink, path)

    # TODO: Edit files stored in temporary file
    edit_files(path)

    # TODO: Move files stored in temporary file
    move_files(arguments, path)

    if False:
        sys.exit(1)


# Main Execution

if __name__ == '__main__':
    main()
