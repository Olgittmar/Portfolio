import unittest

from solutions.point_in_polygon.solution import point_in_polygon

# This naming comvention really sucks, should do something about that...
class TestSolution(unittest.TestCase):
    
    #TODO Read cases and answers from generate_test_data
    def test_point_in_polygon(self, cases, answers):
        for case, answer in zip(cases, answers):
            self.assertMultiLineEqual(point_in_polygon(case), answer)

if __name__ == '__main__':
    unittest.main()