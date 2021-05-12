
def generate_test_data( solution_name ):
    cases, answers = "", ""
    # No autogenerating edge-cases yet, so read the from file instead.
    if solution_name == 'point_in_polygon':
        with open('input.in') as f:
            cases = f.readlines()
        with open('output.ans') as f:
            answers = f.readlines()
    return cases, answers