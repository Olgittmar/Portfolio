import pathlib

def generate_test_data( solution_name ):
    cases, answers = "", ""
    # No autogenerating edge-cases yet, so read the from file instead.
    if solution_name == 'point_in_polygon':
        base = pathlib.Path("data/")
        with base.joinpath("point_in_polygon.in").open() as f:
            cases = f.readlines()
        with base.joinpath("point_in_polygon.ans").open() as f:
            answers = f.readlines()
    return cases, answers