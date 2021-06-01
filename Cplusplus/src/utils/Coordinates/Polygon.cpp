#include "Polygon.h"

#include "../StringUtils/StringUtils.h"

namespace utils {

Polygon::Polygon(const string& str)
{
    this->_vertices = Point::str_to_points(str, '\n', ' ');
}

Polygon::Polygon(const vector<Point>& points) : _vertices(points){}

string
Polygon::classify(const Point p) const
{
    // No vertices, no points included
    if( _vertices.empty() ){
        return "out";
    }
    // Only one vertice, then p can only be included if it is the same point.
    // The edge case where we have 2 points should be included in the algorithm below,
    // compiler will probably not figure it out, but performance should be plenty good in that case anyway.
    if( _vertices.size() == 1 ){
        if( _vertices.front() == p ){
            return "on";
        } else {
            return "out";
        }
    }
    Line line;
    Point lineStart, lineEnd;
    int numIntersects = 0;
    // We have enough vertices, so lets iterate through and see how many times
    // a beam out from p will intersect the lines between our vertices.
    auto it = _vertices.cbegin();
    do {
        lineStart = *(it++);
        if ( it == _vertices.cend() ){
            lineEnd = _vertices.front();
        } else {
            lineEnd = *(it++);
        }
        line = Line( lineStart, lineEnd );
        if( line.includes(p) ){
            return "on";
        }
        if( line.intersects(p) ){
            numIntersects++;
        }
    } while ( it != _vertices.cend() );
    if ( numIntersects % 2 != 0 ){
        return "in";
    } else {
        return "out";
    }
}

void
Polygon::readPolygon( istream& in, const int numLines, utils::Polygon& out ) {
    string line;
    utils::Point p;
    for( int i = 0; i < numLines; i++ ){
        getline( in, line );
        p = utils::Point( line );
        out.addPoint( p );
    }
}

} // namespace utils