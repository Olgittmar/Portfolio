# Own
from src.utils.coordinates import *

def point_in_polygon(data):
    case = 0
    index = 0
    polygons = {}
    test_points = {}
    _ret = ""
    # Read all polygons and points to test
    # Test cases should be terminated with a 0, but just to be sure we check the length as well.
    while index < len(data):
        # Define polygon with points in some order.
        num_vertices = int( data[index] )
        if not num_vertices > 0:
            break
        index = index + 1
        for line in data[index : index + num_vertices]:
            p = Point.from_str(line)
            if case not in polygons:
                polygons[case] = [p]
            else:
                polygons[case].append( p )
        index += num_vertices
        # Define list of points to test
        num_test_points = int( data[index] )
        index += 1
        for line in data[index : index + num_test_points]:
            p = Point.from_str(line)
            if case not in test_points:
                test_points[case] = [p]
            else:
                test_points[case].append( p ) # Might need to check if there is a list at this pos first.
        index += num_test_points
        # Jump ahead to next test case
        case += 1
    # pos should now be the index of the last line in the input file. Could also use zip i guess
    # For every pair of polygon and set of points, test if the points are in, outside or on the polygon.
    for i in range(case):
        for point in test_points[i]:
            res_ = is_inside(polygons[i], point)
            _ret += res_ + '\n'
            # _ret += is_inside(polygons[i], point) + '\n'
    return _ret

# ---------------------------------------------------------------------------------------------------------------------
def is_inside( polygon, p ):
    num_intersections = 0
    i = 0
    # For every linesegment in the polygon
    # Check if the line intersects the line between the test_point and the horizontal beam to +infinity
    # If the number of intersections are even, the point must either be outside the polygon,
    # or the vertice lies on the beam.
    while i < len(polygon):
        # The last line should end at the first vertice again.
        line_ = Line( polygon[i], ( polygon[i+1] if i+1 < len(polygon) else polygon[0] ) )
        i += 1
        if line_.includes(p):
            return 'on'
        if not line_.in_y_range(p.y):
            # Will the compiler figure out we already tested this?
            continue
        if not line_.is_to_right_of_or_might_include(p):
            continue
        num_intersections += 1
    if num_intersections % 2 == 0:
        return 'out'
    else:
        return 'in'