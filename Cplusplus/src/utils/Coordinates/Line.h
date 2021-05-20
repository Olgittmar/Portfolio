#pragma once

// std
#include <string>
#include <math.h>

// Own
#include "Point.h"

using namespace std;
namespace utils {

class Line {
  public:
    Line() = default;
    ~Line() = default;
    Line( const Point start, const Point end );
    Line( const int start_x, const int start_y, const int end_x, const int end_y );
    Line( const string str );
    
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

  protected:
  private:
    int dx() const;
    int dy() const;
    Point _start;
    Point _end;
};

}