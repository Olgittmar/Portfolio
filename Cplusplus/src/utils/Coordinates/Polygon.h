#pragma once

// std
#include <string>
#include <vector>

// Own
#include "Point.h"
#include "Line.h"

using namespace std;

namespace utils {

class Polygon {
  public:
    Polygon() = default;
    ~Polygon() = default;
    Polygon(const string str);
    Polygon(const vector<Point> points);

    // Returns true if the point p is inside this polygon
    bool surrounds( const Point p ) const;
    // Classifies the point p and returns a string with the corresponding classification,
    // "out" if p is outside the polygon
    // "in" if p is inside the polygon
    // "on" if p is on one or more of the lines between _vertices
    string classify( const Point p ) const;

  protected:
  private:
    // The vertices that make up this polygon,
    // either in clockwise or counter-clockwise order
    vector<Point> _vertices;
};

} // namespace utils