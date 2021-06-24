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

Point
Line::aboveLine( const Line& theLine ) {
    return Point(
        theLine.midpoint().x(),
        max( theLine.start().y(), theLine.end().y() ) + 1
    );
}

Point
Line::belowLine( const Line& theLine ) {
    return Point(
        theLine.midpoint().x(),
        min( theLine.start().y(), theLine.end().y() ) - 1
    );
}

Point
Line::leftOfLine( const Line& theLine ) {
    return Point(
        min( theLine.start().x(), theLine.end().x() ) - 1,
        theLine.midpoint().y()
    );
}

Point
Line::rightOfLine( const Line& theLine ) {
    return Point(
        max( theLine.start().x(), theLine.end().x() ) + 1,
        theLine.midpoint().y()
    );
}

Point
Line::aboveMidpoint( const Line& theLine ) {
    return Point(
        theLine.midpoint().x(),
        theLine.midpoint().y() + 1
    );
}

Point
Line::belowMidpoint( const Line& theLine ) {
    return Point(
        theLine.midpoint().x(),
        theLine.midpoint().y() - 1
    );
}

Point
Line::leftOfMidpoint( const Line& theLine ) {
    return Point(
        theLine.midpoint().x() - 1,
        theLine.midpoint().y()
    );
}

Point
Line::rightOfMidpoint( const Line& theLine ) {
    return Point(
        theLine.midpoint().x() + 1,
        theLine.midpoint().y()
    );
}

double
Line::slope() const
{
    if( dx() == 0 ) {
    	return INFINITY;
    }
    return ((double)dy()/(double)dx());
}

double
Line::invSlope() const
{
    if( dy() == 0 ) {
    	return INFINITY;
    }
    return ((double)dx()/(double)dy());
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
    return !( dx() == 0 || dy() == 0 );
}

double
Line::yAt( const int x ) const
{
    if ( !isAngled() ){
        if( slope() == 0 ){
            return _start.y();
        } else {
            throw exception("Math error: yAt value is undefined, line is vertical");
        }
    } else {
        // For extremely long lines it might make a difference which point we use as reference
        return (_start.y() + (x - _start.x())*slope() );
    }
}

double
Line::xAt( const int y ) const
{
    if ( !isAngled() ){
        if( invSlope() == 0 ){
            return _start.x();
        } else {
            throw exception("Math error: xAt value is undefined, line is horizontal");
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
                throw exception("Unexpected quadrant somehow encountered!");
        }
    }
}

bool
Line::includes( const Point p ) const
{
    if( p==_start || p==_end ){
        // Should fix some edgecases, also slightly faster in those cases.
        return true;
    }
    if( !inHRange( p.x() ) ){
        return false;
    }
    if( !inVRange( p.y() ) ){
        return false;
    }
    if( !isAngled() ){
        // If the line is vertical or horizontal, the above checks are enough to guarantee that the point is on the line.
        return true;
    }
    if( yAt( p.x() ) == p.y() ){
        return true;
    }
    // Potentially we could fail the above due to rounding error test if dx is very large
    // So let's test the other way around as well, otherwise we'll have to say it's not included.
    return xAt( p.y() ) == p.x();
}

ostream&
operator<<(ostream& os, const Line& theLine )
{
    os << theLine._start << " - " << theLine._end;
    return os;
}

} // namespace utils