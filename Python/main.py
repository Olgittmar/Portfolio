# -------------------------------------------------------------------------------------------
# Command line interface used to run a solution specified with -s SoleSolution,
# with the input file specified with -f Full/Path/To/input_file.in
# outputting the result to the output file specified with -o Full/Path/To/output_file.ans
#
# The interface should be able to handle stdin as input and stdout as output
# Note that the requested solution name must be available as a callable in file scope
# for the program to recognize it. For now it is also case sensitive.
# -------------------------------------------------------------------------------------------
import sys
import os
import traceback
import argparse

# Own
# These beautiful imports are needed during runtime for the program to be able to
# identify which solutions are available to run
from solutions.point_in_polygon.solution import point_in_polygon

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
    # cl_opt (CommandLine OPTions) contains the parsed command line arguments;
    # input/output file, which solution to run etc.
    cl_opt = parse_and_verify_input()
    try:
        data = read_input(cl_opt)
        func = globals()[cl_opt[SOLUTION]]
        results = func(data)
        write_output( results, cl_opt )
    except InvalidInputFileError as err:
        print('No input file specified: %s' % err.args )
    except InvalidSolutionFuncError as err:
        print('Invalid solution: %s' % err.args)
    except Exception as err:
        traceback.print_exc()
        pass
    return 0

# Parse command line arguments and verify that they are useable.
# Note that argparse already verifies that the input and output files are useable.
def parse_and_verify_input():
    parser = init_argparse()
    # 'vars()' is just to get the parsed arguments as a dict,
    args = vars( parser.parse_args(args=sys.argv[1:]) )
    # Verify that the solution user specified is a function that actually exists
    if args[SOLUTION] not in globals():
         raise InvalidSolutionFuncError
    # Is it actually a callable function?
    if not callable( globals()[args[SOLUTION]] ):
        raise InvalidSolutionFuncError
    return args

# Read input from filename defined in cl_opt
# returns result as a list of strings
def read_input(cl_opt):
    data = ""
    with open(cl_opt[INPUT_FILE].name) as f:
        data = f.readlines()
    return data

# res = results to be printed
# writes result to filename specified in cl_opt
def write_output(res, cl_opt):
    if cl_opt[OUTPUT_FILE] is not None:
        print(res, file=cl_opt[OUTPUT_FILE])
    else:
        print(res)
    return
    
if __name__ == '__main__':
    main()