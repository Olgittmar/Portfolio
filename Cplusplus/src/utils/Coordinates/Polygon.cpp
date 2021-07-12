#include "Polygon.h"

#include "../StringUtils/StringUtils.h"

namespace utils {

Polygon::Polygon(const string& str)
{
    this->_vertices = Point::str_to_points(str, '\n', ' ');
}

Polygon::Polygon(const vector<Point>& points) : _vertices(points){}

Polygon::_Iterator::reference
Polygon::_Iterator::operator*() const
{
    if( m_it == _container.cend() - 1 ){
        return Line( *m_it, *_container.cbegin() );
    } else {
        return Line( *m_it, *(m_it + 1) );
    }
}

bool
Polygon::operator==( const Polygon& other ) const
{
    if( numVertices() != other.numVertices() ){
        return false;
    }

    auto myIt = cbegin();
    auto otherIt = other.cbegin();
    while( myIt != cend() && otherIt != other.cend() ) {
        if( *myIt != *otherIt ){
            return false;
        }
        // Encountered interesting crash here when incrementing the iterators inside the
        // if-expression. Because I haven't defined my operator++ for post-increments,
        // the expression *(myIt++) isn't valid.
        // TODO: fix this for prettier syntax
        ++myIt;
        ++otherIt;
    }
    return true;
}

string
Polygon::classify(const Point p) const
{
    // No vertices, no points included
    if( _vertices.empty() ){
        return "out";
    }
    int numIntersects = 0;
    // If the point on any of the lines that make up this polygon, we return 'on'
    // If the beam from the point horizontally to the right intersects an odd number of lines
    // then it must be inside the polygon.
    // Note: The endpoints of lines will be counted twice, so hitting an acute edge will not
    // produce a false positive.
    for( auto line : *this ){
        if( line.includes(p) ){
            return "on";
        }
        if( line.intersects(p) ){
            numIntersects++;
        }
    }
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

ostream&
operator<<(ostream& os, const Polygon& poly)
{
    for( auto pIt = poly._vertices.cbegin(); pIt != poly._vertices.cend(); ++pIt ){
        os << *pIt;
        if( pIt != poly._vertices.cend() - 1 ){
            os << '\n';
        }
    }
    return os;
}

} // namespace utils