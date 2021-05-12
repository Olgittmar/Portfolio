import error

# Raised if the specified input file is not found, unreadable or unspecified.
class InvalidInputFileError(Exception):
    pass

# Raised if the specified solution function cannot be called.
class InvalidSolutionFuncError(Exception):
    pass

# Raised if a custom methos was invoked incorrectly
class InvalidUseError(Exception):
    pass

# Raised if the specified solution does not pass the assigned test cases
# class InvalidSolutionError(Exception):
#     pass
# Not yet implemented