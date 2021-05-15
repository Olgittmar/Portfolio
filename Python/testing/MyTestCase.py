import unittest

# Own
from testing.generate_test_data import generate_test_data

# General testcase
# Must be subclassed with a SOLUTION_NAME matching a callable function in globals()
class MyTestCase(unittest.TestCase):
    
    def __init__(self, methodName: str):
        super().__init__('test_solution')
    
    # def test_solution(self):
    #     raise NotImplementedError('MyTestCase must be subclassed.')