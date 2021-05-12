import pathlib

def generate_test_data( solution_name ):
    cases, answers = "", ""
    # No autogenerating edge-cases yet, so read the from file instead.
    if solution_name == 'point_in_polygon':
        solution_path = pathlib.Path("solutions/point_in_polygon/")
        with open(solution_path + 'input.in') as f:
            cases = f.readlines()
        with open(solution_path + 'output.ans') as f:
            answers = f.readlines()
    return cases, answers