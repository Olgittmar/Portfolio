from functools import cache

from src.utils.coordinates import *
from error import InvalidUseError

# Wrapper class for defining a polygon from vertices in order.
# Acts as both a container and iterator, returning the line between the n:th and n+1:th points
class Polygon():
    _vertices = [Point]

    def __init__(self, points):
        self._vertices = points

    def __iter__(self):
        return self.lines_generator()
    
    # returns a generator for the line between vertices
    def lines_generator(self):
        if len(self._vertices) < 3:
            raise RuntimeError('Polygon must consist of at least 3 vertices.')
        _n = 0
        while _n < len(self._vertices):
            yield( self.get_line(_n) )
            _n += 1
    
    @cache
    def get_line(self, n):
        if n < len(self._vertices) - 1:
            return Line( self._vertices[n], self._vertices[n + 1] )
        else:
            return Line( self._vertices[n], self._vertices[0] )
    
    # Does adding a vertice break the generator?
    def add_vertice(self, p):
        try:
            self._vertices.append( p )
        except IndexError as err:
            print('Index error while attempting to add point %s: %s' % p, err.args )
            raise err