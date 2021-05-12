import unittest

# Own
from testing.generate_test_data import generate_test_data

# General testcase
# Must be subclassed with a SOLUTION_NAME matching a callable function in globals()
class MyTestCase(unittest.TestCase):
    SOLUTION_NAME = ''

    def setUp(self):
        self._cases, self._answers = generate_test_data(self.SOLUTION_NAME)

    #TODO Read cases and answers from generate_test_data
    def test_solution(self):
        func = globals()[self.SOLUTION_NAME]
        self.failUnless(callable(func), "Solution not found." )
        self.assertIsNotNone(self._cases)
        self.assertIsNotNone(self._answers)
        for case, answer in zip(self._cases, self._answers):
            self.assertMultiLineEqual( func(case), answer )
