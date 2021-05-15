import pathlib

def generate_test_data( solution_name ):
    cases, answers = "", ""
    # No autogenerating edge-cases yet, so read the from file instead.
    if solution_name == 'point_in_polygon':
        base = pathlib.Path("Python/solutions/point_in_polygon/")
        with base.joinpath("input.in").open() as f:
            cases = f.readlines()
        with base.joinpath("output.ans").open() as f:
            answers = f.readlines()
    return cases, answers