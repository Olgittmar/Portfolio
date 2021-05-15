import unittest

# Own
from solutions.point_in_polygon.solution import point_in_polygon
from testing.generate_test_data import generate_test_data
from testing.MyTestCase import MyTestCase

class test_point_in_polygon(unittest.TestCase):
    SOLUTION_NAME = 'point_in_polygon'

    def setUp(self):
        self._cases, self._answers = generate_test_data(self.SOLUTION_NAME)
        return super().setUp()

    def test_solution(self):
        func = globals()[self.SOLUTION_NAME]
        self.assertTrue(callable(func), "Solution not found." )
        self.assertIsNotNone(self._cases)
        self.assertIsNotNone(self._answers)
        self.assertMultiLineEqual( func(self._cases) , ''.join(self._answers) )