import unittest

from src.utils.coordinates import *

# Keywords
START = 'start'
END = 'end'
LINE = 'line'
INV_LINE = 'inv_line'
LEFT = 'left'
RIGHT = 'right'
UP = 'up'
DOWN = 'down'
CLOSE_LEFT = 'close_left'
CLOSE_RIGHT = 'close_right'
CLOSE_UP = 'close_up'
CLOSE_DOWN = 'close_down'
BEFORE = 'before'
AFTER = 'after'

class TestCoordinates(unittest.TestCase):
    data = {}

    def setUp(self):
        self.data[START] = Point(0, 5) # botton left
        self.data[END] = Point(20, 0) # top right
        self.data[LINE] = Line( self.data[START], self.data[END] ) # The test_line
        # Different orientation of lines
        self.data[INV_LINE] = Line( self.data[END], self.data[START] )

        # to the left of midpoint
        self.data[LEFT] = Point( min(self.data[START].x, self.data[END].x) - 1, self.data[LINE].v_midpoint() )
        # to the right of midpoint
        self.data[RIGHT] = Point( max(self.data[START].x, self.data[END].x) + 1, self.data[LINE].v_midpoint() )
        # above midpoint
        self.data[UP] = Point( self.data[LINE].h_midpoint(), max( self.data[START].y, self.data[END].y) + 1 )
        # below midpoint
        self.data[DOWN] = Point( self.data[LINE].h_midpoint(), min( self.data[START].y, self.data[END].y ) - 1 )
        # to left of x-range
        self.data[CLOSE_LEFT] = Point( self.data[LINE].h_midpoint() - 1, self.data[LINE].v_midpoint() )
        # to right of x-range
        self.data[CLOSE_RIGHT] = Point( self.data[LINE].h_midpoint() + 1, self.data[LINE].v_midpoint() )
        # above y-range
        self.data[CLOSE_UP] = Point( self.data[LINE].h_midpoint(), self.data[LINE].v_midpoint() + 1 )
        # below y-range
        self.data[CLOSE_DOWN] = Point( self.data[LINE].h_midpoint(), self.data[LINE].v_midpoint() - 1 )
        # along line, but outside range
        self.data[BEFORE] = Point(
            self.data[START].x + (1 if self.data[START].x > 0 else -1),
            self.data[START].y + (1 if self.data[START].y > 0 else -1) )
        self.data[AFTER] = Point(
            self.data[END].x + (1 if self.data[END].x > 0 else -1),
            self.data[END].y + (1 if self.data[END].y > 0 else -1) )

    def test_point(self):
        self.assertNotEqual( Point(5,6), Point(4,5) )
        self.assertEqual( Point(5,6), Point(5,6) )
        self.assertEqual( Point(5,6), Point(5,6) )
        self.assertNotEqual( Point(5,5), Point(-5,5) )
        self.assertEqual( Point(5,6), Point.from_str('5 6'))
        self.assertEqual( Point(-5,6), Point.from_str('-5 6'))
        self.assertEqual( Point(5,-6), Point.from_str('5 -6'))
        # Class is really basic, but should probably test for invalid inits as well...

    def test_line_init(self):
        self.assertEqual( self.data[LINE].start, self.data[START] )
        self.assertEqual( self.data[LINE].end, self.data[END] )
        self.assertEqual( self.data[INV_LINE].start, self.data[END] )
        self.assertEqual( self.data[INV_LINE].end, self.data[START] )

    def test_line_in_x_range(self):
        line = self.data[LINE]
        self.assertTrue( line.in_x_range( self.data[START].x ) )
        self.assertTrue( line.in_x_range( self.data[END].x ) )
        self.assertTrue( line.in_x_range( self.data[START] ) )
        self.assertTrue( line.in_x_range( self.data[END] ) )

        self.assertTrue( line.in_x_range(  self.data[UP] ) )
        self.assertTrue( line.in_x_range(  self.data[DOWN] ) )
        self.assertFalse( line.in_x_range( self.data[LEFT] ) )
        self.assertFalse( line.in_x_range( self.data[RIGHT] ) )
        self.assertTrue( line.in_x_range(  self.data[CLOSE_UP] ) )
        self.assertTrue( line.in_x_range(  self.data[CLOSE_DOWN] ) )
        self.assertTrue( line.in_x_range(  self.data[CLOSE_LEFT] ) )
        self.assertTrue( line.in_x_range(  self.data[CLOSE_RIGHT] ) )
        self.assertFalse( line.in_x_range( self.data[BEFORE] ) )
        self.assertFalse( line.in_x_range( self.data[AFTER] ) )

    def test_line_in_y_range(self):
        line = self.data[LINE]
        self.assertTrue( line.in_y_range( self.data[START].y ) )
        self.assertTrue( line.in_y_range( self.data[END].y ) )
        self.assertTrue( line.in_y_range( self.data[START] ) )
        self.assertTrue( line.in_y_range( self.data[END] ) )

        self.assertFalse( line.in_y_range( self.data[UP] ) )
        self.assertFalse( line.in_y_range( self.data[DOWN] ) )
        self.assertTrue( line.in_y_range(  self.data[LEFT] ) )
        self.assertTrue( line.in_y_range(  self.data[RIGHT] ) )
        self.assertTrue( line.in_y_range(  self.data[CLOSE_UP] ) )
        self.assertTrue( line.in_y_range(  self.data[CLOSE_DOWN] ) )
        self.assertTrue( line.in_y_range(  self.data[CLOSE_LEFT] ) )
        self.assertTrue( line.in_y_range(  self.data[CLOSE_RIGHT] ) )
        self.assertFalse( line.in_y_range( self.data[BEFORE] ) )
        self.assertFalse( line.in_y_range( self.data[AFTER] ) )

    def test_line_to_right_or_includes(self):
        line = self.data[LINE]
        self.assertTrue( line.to_right_or_includes(  self.data[START] ) )
        self.assertTrue( line.to_right_or_includes(  self.data[END] ) )
        self.assertFalse( line.to_right_or_includes( self.data[UP] ) )
        self.assertFalse( line.to_right_or_includes( self.data[DOWN] ) )
        self.assertTrue( line.to_right_or_includes(  self.data[LEFT] ) )
        self.assertFalse( line.to_right_or_includes( self.data[RIGHT] ) )
        self.assertFalse( line.to_right_or_includes( self.data[CLOSE_UP] ) )
        self.assertTrue( line.to_right_or_includes(  self.data[CLOSE_DOWN] ) )
        self.assertTrue( line.to_right_or_includes(  self.data[CLOSE_LEFT] ) )
        self.assertFalse( line.to_right_or_includes( self.data[CLOSE_RIGHT] ) )
        self.assertFalse( line.to_right_or_includes( self.data[BEFORE] ) )
        self.assertFalse( line.to_right_or_includes( self.data[AFTER] ) )

        inv_line = self.data[INV_LINE]
        self.assertTrue( inv_line.to_right_or_includes(  self.data[START] ) )
        self.assertTrue( inv_line.to_right_or_includes(  self.data[END] ) )
        self.assertFalse( inv_line.to_right_or_includes( self.data[UP] ) )
        self.assertFalse( inv_line.to_right_or_includes( self.data[DOWN] ) )
        self.assertTrue( inv_line.to_right_or_includes(  self.data[LEFT] ) )
        self.assertFalse( inv_line.to_right_or_includes( self.data[RIGHT] ) )
        self.assertFalse( inv_line.to_right_or_includes( self.data[CLOSE_UP] ) )
        self.assertTrue( inv_line.to_right_or_includes(  self.data[CLOSE_DOWN] ) )
        self.assertTrue( inv_line.to_right_or_includes(  self.data[CLOSE_LEFT] ) )
        self.assertFalse( inv_line.to_right_or_includes( self.data[CLOSE_RIGHT] ) )
        self.assertFalse( inv_line.to_right_or_includes( self.data[BEFORE] ) )
        self.assertFalse( inv_line.to_right_or_includes( self.data[AFTER] ) )


if __name__ == '__main__':
    unittest.main()