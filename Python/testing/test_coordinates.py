import unittest

from src.utils.coordinates import *


class TestCoordinates(unittest.TestCase):
    DEFAULT_START = (-4, 5)
    DEFAULT_END = (10, 10)

    def __init__(self, methodName: str, start: tuple[int, int] = DEFAULT_START, end: tuple[int,int] = DEFAULT_END) -> None:
        # Init the start and end of the line to test
        self.START = Point.from_tuple(start)
        self.END = Point.from_tuple(end)
        # The line to test
        self._line = Line( self.START, self.END )
        # Inverse direction of line
        self._inv_line = Line( self.END, self.START )
        # to the left of midpoint
        self.LEFT = Point( min(self.START.x, self.END.x) - 1, self._line.v_midpoint() )
        # to the right of midpoint
        self.RIGHT = Point( max(self.START.x, self.END.x) + 1, self._line.v_midpoint() )
        # above midpoint
        self.UP = Point( self._line.h_midpoint(), max( self.START.y, self.END.y) + 1 )
        # below midpoint
        self.DOWN = Point( self._line.h_midpoint(), min( self.START.y, self.END.y ) - 1 )
        # to left of x-range
        self.CLOSE_LEFT = Point( self._line.h_midpoint() - 1, self._line.v_midpoint() )
        # to right of x-range
        self.CLOSE_RIGHT = Point( self._line.h_midpoint() + 1, self._line.v_midpoint() )
        # above y-range
        self.CLOSE_UP = Point( self._line.h_midpoint(), self._line.v_midpoint() + 1 )
        # below y-range
        self.CLOSE_DOWN = Point( self._line.h_midpoint(), self._line.v_midpoint() - 1 )
        # Along line, but outside range. Relies on x_at(y) and y_at(x) to work correctly
        #! Note that for the test below we use the leftmost point as Before, and the rightmost point as AFTER
        if self._line.slope_quadrant() in [1,4]:
            self.BEFORE = Point( self.START.x - 1, self._line.y_at( self.START.x - 1 ) )
            self.AFTER = Point( self.END.x + 1, self._line.y_at( self.END.x + 1 ) )
        if self._line.slope_quadrant() in [2,3]:
            self.BEFORE = Point( self.END.x - 1, self._line.y_at( self.END.x - 1 ) )
            self.AFTER = Point( self.START.x + 1, self._line.y_at( self.START.x + 1 ) )
        if self._line.slope_quadrant() == 0:
            if self._line.slope() == 0:
                self.BEFORE = Point( self.START.x - 1, self.START.y )
                self.AFTER = Point( self.END.x + 1, self.START.y )
            else:
                self.BEFORE = Point( self.START.x, self.START.y - 1 )
                self.AFTER = Point( self.END.x, self.START.y + 1 )
        super().__init__(methodName=methodName)

    def test_point_init(self):
        self.assertNotEqual( Point(5,6), Point(4,5) )
        self.assertEqual( Point(5,6), Point(5,6) )
        self.assertEqual( Point(5,6), Point(5,6) )
        self.assertNotEqual( Point(5,5), Point(-5,5) )
        self.assertEqual( Point(5,6), Point.from_str('5 6'))
        self.assertEqual( Point(-5,6), Point.from_str('-5 6'))
        self.assertEqual( Point(5,-6), Point.from_str('5 -6'))
        # Should work I think, as long as there is a ' ' in between the coordinates and
        # the substrings are convertible to ints
        self.assertEqual( Point(5,-6), Point.from_str('5\n -6'))
        self.assertEqual( Point(0, 1), Point.from_tuple((0, 1)))
        #TODO Class is really basic, but should probably test for invalid inits as well...

    def test_line_init(self):
        self.assertEqual( self._line.start, self.START )
        self.assertEqual( self._line.end, self.END )
        self.assertEqual( self._inv_line.start, self.END )
        self.assertEqual( self._inv_line.end, self.START )
        #? Unsure what tests should be included in init
    
    def test_line_x_at(self):
        self.assertTrue( self._line.x_at( self.START.y ) == self.START.x )
        self.assertTrue( self._line.x_at( self.START.y ) == self.START.x )
        self.assertTrue( self._line.x_at( self.END.y ) == self.END.x )
        self.assertTrue( self._line.x_at( self.END.y ) == self.END.x )
        self.assertTrue( self._line.h_midpoint() == self._line.x_at( self._line.v_midpoint() ) )

    def test_line_y_at(self):
        self.assertTrue( self._line.y_at( self.START.x ) == self.START.y )
        self.assertTrue( self._line.y_at( self.START.x ) == self.START.y )
        self.assertTrue( self._line.y_at( self.END.x ) == self.END.y )
        self.assertTrue( self._line.y_at( self.END.x ) == self.END.y )
        self.assertTrue( self._line.v_midpoint() == self._line.y_at( self._line.h_midpoint() ) )

    def test_line_start(self):
        self.assertTrue( self._line.in_x_range( self.START.x ) )
        self.assertTrue( self._line.in_x_range( self.START ) )
        self.assertTrue( self._inv_line.in_x_range( self.START.x ) )
        self.assertTrue( self._inv_line.in_x_range( self.START ) )

        self.assertTrue( self._line.in_y_range( self.START.y ) )
        self.assertTrue( self._line.in_y_range( self.START ) )
        self.assertTrue( self._inv_line.in_y_range( self.START.y ) )
        self.assertTrue( self._inv_line.in_y_range( self.START ) )
        
        self.assertTrue( self._line.is_to_right_of_or_might_include(  self.START ) )
        self.assertTrue( self._inv_line.is_to_right_of_or_might_include(  self.START ) )

    def test_line_end(self):
        self.assertTrue( self._line.in_x_range( self.END.x ) )
        self.assertTrue( self._line.in_x_range( self.END ) )
        self.assertTrue( self._inv_line.in_x_range( self.END.x ) )
        self.assertTrue( self._inv_line.in_x_range( self.END ) )

        self.assertTrue( self._line.in_y_range( self.END.y ) )
        self.assertTrue( self._line.in_y_range( self.END ) )
        self.assertTrue( self._inv_line.in_y_range( self.END.y ) )
        self.assertTrue( self._inv_line.in_y_range( self.END ) )

        self.assertTrue( self._line.is_to_right_of_or_might_include(  self.END ) )
        self.assertTrue( self._inv_line.is_to_right_of_or_might_include(  self.END ) )

    def test_line_up(self):
        self.assertTrue( self._line.in_x_range(  self.UP ) )
        self.assertTrue( self._inv_line.in_x_range(  self.UP ) )

        self.assertFalse( self._line.in_y_range( self.UP ) )
        self.assertFalse( self._inv_line.in_y_range( self.UP ) )

        self.assertFalse( self._line.is_to_right_of_or_might_include( self.UP ) )
        self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.UP ) )

    def test_line_down(self):
        self.assertTrue( self._line.in_x_range(  self.DOWN ) )
        self.assertTrue( self._inv_line.in_x_range(  self.DOWN ) )

        self.assertFalse( self._line.in_y_range( self.DOWN ) )
        self.assertFalse( self._inv_line.in_y_range( self.DOWN ) )

        self.assertFalse( self._line.is_to_right_of_or_might_include( self.DOWN ) )
        self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.DOWN ) )

    def test_line_left(self):
        self.assertFalse( self._line.in_x_range( self.LEFT ) )
        self.assertFalse( self._inv_line.in_x_range( self.LEFT ) )

        self.assertTrue( self._line.in_y_range(  self.LEFT ) )
        self.assertTrue( self._inv_line.in_y_range(  self.LEFT ) )
        
        self.assertTrue( self._line.is_to_right_of_or_might_include(  self.LEFT ) )
        self.assertTrue( self._inv_line.is_to_right_of_or_might_include(  self.LEFT ) )

    def test_line_right(self):
        self.assertFalse( self._line.in_x_range( self.RIGHT ) )
        self.assertFalse( self._inv_line.in_x_range( self.RIGHT ) )

        self.assertTrue( self._line.in_y_range(  self.RIGHT ) )
        self.assertTrue( self._inv_line.in_y_range(  self.RIGHT ) )
        
        self.assertFalse( self._line.is_to_right_of_or_might_include( self.RIGHT ) )
        self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.RIGHT ) )

    # This got complicated...
    def test_line_close_up(self):
        self.assertTrue( self._line.in_x_range(  self.CLOSE_UP ) )
        self.assertTrue( self._inv_line.in_x_range(  self.CLOSE_UP ) )
        if abs( self._line.start.y - self._line.end.y ) >= 2:
            self.assertTrue( self._line.in_y_range(  self.CLOSE_UP ) )
            self.assertTrue( self._inv_line.in_y_range(  self.CLOSE_UP ) )
        else:
            self.assertFalse( self._line.in_y_range(  self.CLOSE_UP ) )
            self.assertFalse( self._inv_line.in_y_range(  self.CLOSE_UP ) )
        if self._line.slope_quadrant() in [1,4]:
            self.assertTrue( self._line.is_to_right_of_or_might_include(  self.CLOSE_UP ) )
            self.assertTrue( self._inv_line.is_to_right_of_or_might_include(  self.CLOSE_UP ) )
        elif self._line.slope_quadrant() in [2,3]:
            self.assertFalse( self._line.is_to_right_of_or_might_include( self.CLOSE_UP ) )
            self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_UP ) )
        elif self._line.slope_quadrant() == 0:
            if self._line.slope() == 0:
                self.assertFalse( self._line.is_to_right_of_or_might_include( self.CLOSE_UP ) )
                self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_UP ) )
            else:
                if self._line.in_y_range(self.CLOSE_UP):
                    self.assertTrue( self._line.is_to_right_of_or_might_include( self.CLOSE_UP ) )
                    self.assertTrue( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_UP ) )
                else:
                    self.assertFalse( self._line.is_to_right_of_or_might_include( self.CLOSE_UP ) )
                    self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_UP ) )

    def test_line_close_down(self):
        self.assertTrue( self._line.in_x_range(  self.CLOSE_DOWN ) )
        self.assertTrue( self._inv_line.in_x_range(  self.CLOSE_DOWN ) )
        if abs( self._line.start.y - self._line.end.y ) >= 2:
            self.assertTrue( self._line.in_y_range(  self.CLOSE_DOWN ) )
            self.assertTrue( self._inv_line.in_y_range(  self.CLOSE_DOWN ) )
        else:
            self.assertFalse( self._line.in_y_range(  self.CLOSE_DOWN ) )
            self.assertFalse( self._inv_line.in_y_range(  self.CLOSE_DOWN ) )
        if self._line.slope_quadrant() in [1,4]:
            self.assertFalse( self._line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )
            self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )
        elif self._line.slope_quadrant() in [2,3]:
            self.assertTrue( self._line.is_to_right_of_or_might_include(  self.CLOSE_DOWN ) )
            self.assertTrue( self._inv_line.is_to_right_of_or_might_include(  self.CLOSE_DOWN ) )
        elif self._line.slope_quadrant() == 0:
            if self._line.slope() == 0:
                self.assertFalse( self._line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )
                self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )
            else:
                if self._line.in_y_range( self.CLOSE_DOWN ):
                    self.assertTrue( self._line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )
                    self.assertTrue( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )
                else:
                    self.assertFalse( self._line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )
                    self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_DOWN ) )


    def test_line_close_left(self):
        if abs( self._line.start.x - self._line.end.x ) >= 2:
            self.assertTrue( self._line.in_x_range(  self.CLOSE_LEFT ) )
            self.assertTrue( self._inv_line.in_x_range(  self.CLOSE_LEFT ) )
            self.assertTrue( self._line.is_to_right_of_or_might_include(  self.CLOSE_LEFT ) )
            self.assertTrue( self._inv_line.is_to_right_of_or_might_include(  self.CLOSE_LEFT ) )
        else:
            self.assertFalse( self._line.in_x_range(  self.CLOSE_LEFT ) )
            self.assertFalse( self._inv_line.in_x_range(  self.CLOSE_LEFT ) )
            self.assertFalse( self._line.is_to_right_of_or_might_include(  self.CLOSE_LEFT ) )
            self.assertFalse( self._inv_line.is_to_right_of_or_might_include(  self.CLOSE_LEFT ) )
        self.assertTrue( self._line.in_y_range(  self.CLOSE_LEFT ) )
        self.assertTrue( self._inv_line.in_y_range(  self.CLOSE_LEFT ) )


    def test_line_close_right(self):
        if abs( self._line.start.x - self._line.end.x) >= 2:
            self.assertTrue( self._line.in_x_range(  self.CLOSE_RIGHT ) )
            self.assertTrue( self._inv_line.in_x_range(  self.CLOSE_RIGHT ) )
        else:
            self.assertFalse( self._line.in_x_range(  self.CLOSE_RIGHT ) )
            self.assertFalse( self._inv_line.in_x_range(  self.CLOSE_RIGHT ) )
        self.assertTrue( self._line.in_y_range(  self.CLOSE_RIGHT ) )
        self.assertTrue( self._inv_line.in_y_range(  self.CLOSE_RIGHT ) )
        self.assertFalse( self._line.is_to_right_of_or_might_include( self.CLOSE_RIGHT ) )
        self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.CLOSE_RIGHT ) )            

    def test_line_before(self):
        self.assertFalse( self._line.in_x_range( self.BEFORE ) )
        self.assertFalse( self._inv_line.in_x_range( self.BEFORE ) )

        self.assertFalse( self._line.in_y_range( self.BEFORE ) )
        self.assertFalse( self._inv_line.in_y_range( self.BEFORE ) )

        if (self._line.slope_quadrant() == 0 and
            self._line.slope() == 0 ):
            self.assertTrue( self._line.is_to_right_of_or_might_include( self.BEFORE ) )
            self.assertTrue( self._inv_line.is_to_right_of_or_might_include( self.BEFORE ) )
        else:
            self.assertFalse( self._line.is_to_right_of_or_might_include( self.BEFORE ) )
            self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.BEFORE ) )

    def test_line_after(self):
        self.assertFalse( self._line.in_x_range( self.AFTER ) )
        self.assertFalse( self._inv_line.in_x_range( self.AFTER ) )

        self.assertFalse( self._line.in_y_range( self.AFTER ) )
        self.assertFalse( self._inv_line.in_y_range( self.AFTER ) )

        self.assertFalse( self._line.is_to_right_of_or_might_include( self.AFTER ) )
        self.assertFalse( self._inv_line.is_to_right_of_or_might_include( self.AFTER ) )
    
    def test_all_points_on_line(self):
        #! Overkill test
        # Check is_to_right_of_or_might_include for every triad of points on, to the left and to the right of the line
        diff = int(self._line.start.x - self._line.end.x)
        for i in range(diff):
            point_on_line = Point(self._line.start.x + i, self._line.start.y + self._line.slope*i)
            point_to_right = Point(self._line.start.x + i, self._line.start.y + self._line.slope*i)
            point_to_left = Point(self._line.start.x + i, self._line.start.y + self._line.slope*i)
            self.assertTrue( self._line.is_to_right_of_or_might_include( point_on_line ) )
            self.assertTrue( self._line.includes( point_on_line ) )
            self.assertFalse( self._line.includes( point_to_right ) )
            self.assertFalse( self._line.includes( point_to_left ) )
            # is_to_right_of_or_might_include refers to that the line is to the right of the given point
            self.assertTrue( self._line.is_to_right_of_or_might_include( point_to_left ) )
            self.assertFalse( self._line.is_to_right_of_or_might_include( point_to_right ) )
            # Check the inverted line to be safe
            self.assertTrue( self._inv_line.is_to_right_of_or_might_include( point_on_line ) )
            self.assertTrue( self._inv_line.is_to_right_of_or_might_include( point_to_left ) )
            self.assertFalse( self._inv_line.is_to_right_of_or_might_include( point_to_right ) )