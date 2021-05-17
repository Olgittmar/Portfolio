# ---------------------------------------------------------------------------------------------------------------------
# Point
# Represents a mathematical point with integer coordinates
from functools import cache
from math import inf


class Point:
    x : int
    y : int

    def __init__(self, x: int = 0, y: int = 0):
        self.x = x
        self.y = y
    
    @classmethod
    def from_str(self, point_str: str):
        x,y = point_str.split(' ')
        return Point( int(x) , int(y) )
    
    @classmethod
    def from_tuple(self, p: tuple[int, int]):
        x,y = p
        return Point( int(x) , int(y) )

    def __eq__(self, other):
        try:
            return (self.x == other.x and self.y == other.y)
        except AttributeError:
            return NotImplemented

# ---------------------------------------------------------------------------------------------------------------------

class Line:
    start : Point
    end : Point

    def __init__(self, start_point: Point, end_point: Point):
        self.start = start_point
        self.end = end_point
    
    @cache
    def h_midpoint(self):
        return ( min( self.start.x, self.end.x) +
               abs( self.end.x - self.start.x )/2 )
    
    @cache
    def v_midpoint(self):
        return ( min( self.start.y, self.end.y) +
               abs( self.end.y - self.start.y )/2 )

    #? Does Python not have overload by type in some form?
    # It does, kindof, but so far this seems to be the best way to reuse the same method name.
    # Which appears to be bad practice in python, since attributes and methods are supposed to have unique identifiers
    def _in_y_range(self, y) -> bool:
        return (y >= min( self.start.y, self.end.y )
            and y <= max( self.start.y, self.end.y ) )
        
    def _in_x_range(self, x) -> bool:
        return (x >= min( self.start.x, self.end.x )
            and x <= max( self.start.x, self.end.x ) )
    
    def in_x_range(self, p) -> bool:
        if type(p) == int:
            return self._in_x_range(p)
        elif type(p) == float:
            return self._in_x_range(p)
        elif type(p) == Point:
            return self._in_x_range(p.x)
        else:
            return NotImplemented

    def in_y_range(self, p) -> bool:
        if type(p) == int:
            return self._in_y_range(p)
        elif type(p) == float:
            return self._in_y_range(p)
        elif type(p) == Point:
            return self._in_y_range(p.y)
        else:
            return NotImplemented

    # Returns true if this line is to the right of the point p,
    # also returns true if it's possible that the point is on the line.
    # The confusing latter is to provide an easy check for if we want to check whether
    # if the point is on the line, which is classified different
    #TODO: gotta figure out a better name for this method...
    def is_to_right_of_or_might_include(self, p: Point) -> bool:
        if not self.in_y_range(p.y):
            return False
        if not self.in_x_range(p.x):
            return p.x < min(self.start.x, self.end.x)
        return self.x_at(p.y) >= p.x
    
    def includes(self, p: Point) -> bool:
        if self.start == p or self.end == p:
            return True
        if not self.in_x_range( p.x ):
            return False
        if not self.in_y_range( p.y ):
            return False
        if self.slope_quadrant() != 0:
            if p.y == self.y_at(p.x):
                return True
            return False
        # Since we are within x and y range, and the line is either horizontal or vertical,
        # the point must be included
        return True
    
    # y = kx + m
    # k = dy/dx = slope, m = start.y
    @cache
    def slope(self):
        if self.slope_quadrant() != 0:
            return (self.end.y - self.start.y)/(self.end.x - self.start.x)
        elif self.end.x == self.start.x:
            return inf
        else:
            return 0.0
    
    # dx/dy
    @cache
    def inv_slope(self):
        if self.slope_quadrant() != 0:
            return (self.end.x - self.start.x)/(self.end.y - self.start.y)
        elif self.start.y == self.end.y:
            return inf
        else:
            return 0
    
    # Returns the lines y-value at x
    def y_at(self, x: int):
        if self.slope_quadrant() != 0:
            return self.start.y + self.slope()*( x - self.start.x )
        elif self.slope() == 0:
            return self.start.y
        else:
            # Undefined, since slope is vertical
            raise RuntimeError("Since the line is vertical, the y value at %s is undefined" % x)
    
    # Returns the lines x-value at y
    def x_at(self, y: int):
        if self.slope_quadrant() != 0:
            return self.start.x + self.inv_slope()*( y - self.start.y )
        if self.slope() == inf:
            return self.start.y
        else:
            raise RuntimeError("Since the line is horizontal, the x value at %s is undefined" % y )

    # Returns the quadrant of the vector pointing from start to end, or 0 if the vector lies on either axis 
    @cache
    def slope_quadrant(self) -> int:
        x_diff = self.start.x - self.end.x
        y_diff = self.start.y - self.end.y
        # upwards to right, /
        if x_diff < 0 and y_diff < 0:
            return 1
        # upwards to left, \
        if x_diff > 0 and y_diff < 0:
            return 2
        # downwards to right, \
        if x_diff < 0 and y_diff > 0:
            return 3
        # downwards to left, /
        if x_diff > 0 and y_diff > 0:
            return 4
        else:
            # The axises mathematically does not really belong to any quadrant,
            # and programmatically, these cases need to be handled separately as the slope is either undefined or 0
            return 0
# ---------------------------------------------------------------------------------------------------------------------