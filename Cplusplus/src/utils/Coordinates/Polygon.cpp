#include "Polygon.h"

#include "StringUtils.h"

using namespace std;

namespace utils {

Polygon::Polygon(const string str)
{
    this->_vertices = Point::str_to_points(str, '\n', ' ');
}

Polygon::Polygon(const vector<Point> points) : _vertices(points){}

bool
Polygon::surrounds(const Point p) const
{
    // Can't surround anything if we ain't got no polygon
    if ( _vertices.size() <= 2 ){
        return false;
    }
    Line line;
    Point lineStart, lineEnd;
    int numIntersects = 0;
    auto it = _vertices.cbegin();
    while ( it != _vertices.cend() ) {
        lineStart = *(it++);
        if ( it == _vertices.cend() ){
            lineEnd = _vertices.front();
        } else {
            lineEnd = *(it++);
        }
        line = Line( lineStart, lineEnd );
        if( line.intersects(p) ){
            numIntersects++;
        }
    }
    return ( numIntersects % 2 != 0 );
}

} // namespace utils