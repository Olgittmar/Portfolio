import unittest

# Own
from solutions.point_in_polygon.solution import point_in_polygon
from testing.generate_test_data import generate_test_data
from testing.MyTestCase import MyTestCase

class test_point_in_polygon(MyTestCase):

    def __init__(self, methodName: str) -> None:
        self.SOLUTION_NAME = 'point_in_polygon'

    def setUp(self) -> None:
        return super().setUp()
    
    def test_solution(self):
        return super().test_solution()