# ---------------------------------------------------------------------------------------------------------------------
# Point
# Represents a mathematical point with integer coordinates
class Point:
    x = 0
    y = 0

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
    
    @classmethod
    def from_str(self, point_str):
        x,y = point_str.split(' ')
        return Point( int(x) , int(y) )
    
    def __eq__(self, other):
        return (self.x == other.x and self.y == other.y)

# ---------------------------------------------------------------------------------------------------------------------

class Line:
    start = Point()
    end = Point()

    def __init__(self, start_point, end_point):
        self.start = start_point
        self.end = end_point
    
    def h_midpoint(self):
        return ( min( self.start.x, self.end.x) +
               ( max( self.start.x, self.end.x ) - min( self.start.x, self.end.x) )/2 )
    
    def v_midpoint(self):
        return ( min( self.start.y, self.end.y) +
               ( max( self.start.y, self.end.y ) - min( self.start.y, self.end.y) )/2 )

    # Does Python not have overload by type in some form?
    def _in_y_range(self, y):
        return (y >= min( self.start.y, self.end.y )
            and y <= max( self.start.y, self.end.y ) )
        
    def _in_x_range(self, x):
        return (x >= min( self.start.x, self.end.x )
            and x <= max( self.start.x, self.end.x ) )
    
    def in_x_range(self, p):
        if type(p) == int:
            return self._in_x_range(p)
        elif type(p) == Point:
            return self._in_x_range(p.x)
        else:
            return RuntimeError('Invalid type of passed object')

    def in_y_range(self, p):
        if type(p) == int:
            return self._in_y_range(p)
        elif type(p) == Point:
            return self._in_y_range(p.y)
        else:
            return RuntimeError('Invalid type of passed object')

    # Returns true if this line is to the right of the point p,
    # also returns true if it's possible that the point is on the line.
    def to_right_or_includes(self, p):
        if not self.in_y_range(p.y):
            return False
        if not self.in_x_range(p.x):
            return p.x < min(self.start.x, self.end.x)
        return self.line_x(p.y) >= p.x
    
    def includes(self, p):
        if self.start == p or self.end == p:
            return True
        if not self.in_x_range( p.x ):
            return False
        if not self.in_y_range( p.y ):
            return False
        print( self.line_y(p.x) )
        if p.y == self.line_y(p.x):
            return True
        return False
    
    # y = kx + m
    # k = slope, m = start.y
    def slope(self):
        return (self.end.y - self.start.y)/(self.end.x - self.start.x)
    
    def inv_slope(self):
        return (self.end.x - self.start.x)/(self.end.y - self.start.y)
    
    # Returns the lines y-value at x
    def line_y(self, x):
        _y = self.start.y + self.slope()*( x - self.start.x )
        return _y
    
    # Returns the lines x-value at y
    def line_x(self, y):
        _x = self.start.x + self.inv_slope()*( y - self.start.y )
        return _x

# ---------------------------------------------------------------------------------------------------------------------