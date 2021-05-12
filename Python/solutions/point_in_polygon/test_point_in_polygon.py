import unittest

# Own
#! Why doesn't pylance resolve in the same way as my interpreter?!?
from solutions.point_in_polygon.solution import point_in_polygon
from src.utils.generate_test_data import generate_test_data
from src.utils.MyTestCase import MyTestCase

class test_point_in_polygon(MyTestCase):

    def __init__(self, methodName: str) -> None:
        self.SOLUTION_NAME = 'point_in_polygon'

    def setUp(self) -> None:
        return super().setUp()
    
    def test_solution(self):
        return super().test_solution()

if __name__ == '__main__':
    unittest.main()