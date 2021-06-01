#include "Line.h"

#include <algorithm>

namespace utils {

// Constructors
Line::Line( const Point& startPoint, const Point& endPoint)
    :_start( startPoint ), _end( endPoint ) {}

Line::Line( const int start_x, const int start_y, const int end_x, const int end_y )
    : _start( start_x, start_y ), _end( end_x, end_y ) {}

Line::Line( const string& str )
{
    vector<pair<int, int>> coords;
    subSplit( str, '\n', ' ', coords );
    this->_start = Point( coords.at( 0 ) );
    this->_end = Point( coords.at( 1 ) );
}

int
Line::dx() const
{
    return ( _end.x() - _start.x() );
}

int
Line::dy() const
{
    return ( _end.y() - _start.y() );
}

double
Line::slope() const
{
    if( dx() == 0 ) {
    	return INFINITY;
    }
    return ( dy()/dx() );
}

double
Line::invSlope() const
{
    if( dy() == 0 ) {
    	return INFINITY;
    }
    return ( dx()/dy() );
}

int
Line::slopeQuadrant() const
{
    if ( dx() > 0 && dy() > 0 ) {
        return 1;
    }
    if ( dx() < 0 && dy() > 0 ) {
        return 2;
    }
    if ( dx() < 0 && dy() < 0 ) {
        return 3;
    }
    if ( dx() > 0 && dy() < 0 ) {
        return 4;
    }
    // If we got here then either dx == 0 or dy == 0,
    // as such the slopeQuadrant is undefined.
    return 0;
}

bool
Line::inHRange( const int x ) const
{
    return ( x >= min( _start.x(), _end.x() )
        &&   x <= max( _start.x(), _end.x() ) );
}

bool
Line::inVRange( const int y ) const
{
    return ( y >= min( _start.y(), _end.y() )
        &&   y <= max( _start.y(), _end.y() ) );
}

bool
Line::isAngled() const
{
    return ( slope() != INFINITY && slope() != 0);
}

double
Line::yAt( const int x ) const
{
    if ( !isAngled() ){
        if( slope() == 0 ){
            return _start.y();
        } else {
            throw exception("Undefined value; line is vertical");
        }
    }
    // For extremely long lines it might make a difference which point we use as reference
    return (_start.y() + (x - _start.x())*slope() );
}

double
Line::xAt( const int y ) const
{
    if ( !isAngled() ){
        if( invSlope() == 0 ){
            return _start.x();
        } else {
            throw exception("Undefined value; line is horizontal");
        }
    }
    return (_start.x() + (y - _start.y())*invSlope() );
}


bool
Line::intersects( const Point p ) const
{
    if( !inVRange( p.y() ) ){
        return false;
    }
    if( !inHRange( p.x() ) ){
        return ( p.x() < min( _start.x(), _end.x() ) );
    } else {
        switch( slopeQuadrant() ){
            case 1:
            case 3:
            {
                return p.y() >= yAt( p.x() );
            }
            break;
            case 2:
            case 4:
            {
                return p.y() <= yAt( p.x() );
            }
            break;
            case 0: {
                // We already know that we are within range.
                return p.x() <= max( _start.x(), _end.x() );
            }
            break;
            default:
                throw exception("Unexpected quadrant somehow ecnountered!");
        }
    }
}

bool
Line::includes( const Point p ) const
{
    if( !inHRange( p.x() ) ){
        return false;
    }
    if( !inVRange( p.y() ) ){
        return false;
    }
    if( yAt( p.x() ) == p.y() ){
        return true;
    }
    // Potentially we could fail the above due to rounding error test if dx is very large
    // So let's test the other way around as well, otherwise we'll have to say it's not included.
    return xAt( p.y() ) == p.x();
}

} // namespace utils