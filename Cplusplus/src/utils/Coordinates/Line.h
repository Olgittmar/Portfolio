#pragma once

// std
#include <string>
#include <math.h>

// Own
#include "Point.h"

namespace utils {
using namespace std;

class Line {
  public:
    Line() = default;
    ~Line() = default;
    Line( const Point& startPoint, const Point& endPoint );
    Line( const int start_x, const int start_y, const int end_x, const int end_y );
    explicit Line( const string& str );

    inline Point start() const { return _start; }
    inline Point end() const { return _end; }
    inline Point midpoint() const {
        return Point( _start.x() + (int)round( dx()/2.0 ),
                      _start.y() + (int)round( dy()/2.0 ) ); }

    static Point start( const Line& theLine );
    static Point end( const Line& theLine );
    static Point aboveLine( const Line& theLine );
    static Point belowLine( const Line& theLine );
    static Point leftOfLine( const Line& theLine );
    static Point rightOfLine( const Line& theLine );
    static Point aboveMidpoint( const Line& theLine );
    static Point belowMidpoint( const Line& theLine );
    static Point leftOfMidpoint( const Line& theLine );
    static Point rightOfMidpoint( const Line& theLine );
    
    // QoL method for Polygon, returns the line from this line's endpoint to the given point.
    inline Line fromEnd( const Point p ) const { return Line( this->_end, p ); }

    double slope() const;
    double invSlope() const;
    int slopeQuadrant() const;
    bool isAngled() const;
    bool inHRange( const int x ) const;
    bool inVRange( const int y ) const;
    double yAt( const int x ) const;
    double xAt( const int y ) const;

    // Returns true if the beam from p to infinity along the horizontal axis
    // intersects this line, including the endpoints, otherwise false
    bool intersects( const Point p ) const;
    // returns true if p is on this line.
    bool includes( const Point p ) const;

    friend ostream& operator<<(ostream& os, const Line& theLine );

  protected:
  private:
    int dx() const;
    int dy() const;
    Point _start;
    Point _end;
};

}