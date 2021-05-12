import sys
import os
import traceback
import argparse

# Own
from solutions.point_in_polygon.solution import point_in_polygon
# Beautiful, I know...

# Definitions
from error import InvalidInputFileError, InvalidSolutionFuncError
from definitions import *

# Input argument parser
def init_argparse() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(usage='%(prog)s [OPTION] [FILE]')
    # Argparse should accept stdin as input file with '-' passed as argument for --f
    parser.add_argument('--f', type=argparse.FileType('r'), help='Input file with inputs for the problem', required=True)
    parser.add_argument('--s', help='Main function for the solution to run', required=True)
    parser.add_argument('--o', type=argparse.FileType('w'), help='File to which the output of the solution function will be written, if none is specified, writes to stdout')
    return parser

def main():
    # cl_opt contains the command line specified options;
    # input/output file, which solution to run etc.
    cl_opt = parse_and_verify_input()
    try:
        data = input(cl_opt)
        func = globals()[cl_opt[SOLUTION]]
        results = func(data)
        output( results, cl_opt )
    except InvalidInputFileError as err:
        print('No input file specified: %s' % err.args )
    except InvalidSolutionFuncError as err:
        print('Invalid solution: %s' % err.args)
    except Exception as err:
        traceback.print_exc()
        pass
    return 0

# Parse command line arguments and verify that they are usable.
def parse_and_verify_input():
    parser = init_argparse()
    args = vars( parser.parse_args(args=sys.argv[1:]) )
    # Verify that the solution user specified is a function that actually exists
    if args[SOLUTION] not in globals():
         raise InvalidSolutionFuncError
    # Is it actually a callable function?
    if not callable( globals()[args[SOLUTION]] ):
        raise InvalidSolutionFuncError
    return args

# Read input from file defined in cl_opt
# source can also be stdin, though this functionality is not verified yet.
def input(cl_opt):
    data = ""
    with open(cl_opt[INPUT_FILE].name) as f:
        data = f.readlines()
    return data

# res = results to be printed
# cl_opt contains info about where the results should be printed.
def output(res, cl_opt):
    if cl_opt[OUTPUT_FILE] is not None:
        print(res, file=cl_opt[OUTPUT_FILE])
    else:
        print(res)
    return
    
if __name__ == '__main__':
    main()