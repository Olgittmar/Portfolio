from parser import suite
import unittest

# Own
import testing.test_coordinates
import testing.test_point_in_polygon

def main_suite():
    suite = unittest.TestSuite()
    suite.addTests( unittest.defaultTestLoader.loadTestsFromTestCase(testing.test_coordinates.TestCoordinates))
    suite.addTests( unittest.defaultTestLoader.loadTestsFromTestCase(testing.test_point_in_polygon.test_point_in_polygon) )
    return suite

if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    runner.run(main_suite())