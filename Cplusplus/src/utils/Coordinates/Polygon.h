#pragma once

// std
#include <string>
#include <vector>

// Own
#include "Point.h"
#include "Line.h"

namespace utils {
using namespace std;

class Polygon {
  public:
    Polygon() = default;
    ~Polygon() = default;
    explicit Polygon(const string& str);
    explicit Polygon(const vector<Point>& points);

    // Classifies the point p and returns a string with the corresponding classification,
    // "out" if p is outside the polygon
    // "in" if p is inside the polygon
    // "on" if p is on one or more of the lines between _vertices
    string classify( const Point p ) const;

    inline void addPoint(const Point& p) { _vertices.push_back( p ); };
    inline void clear() { _vertices.clear(); };
    static void readPolygon( istream& in, const int numLines, utils::Polygon& out );

    // TODO: consider adding STL-style Polygon iterator, it is a container class after all.
  protected:
  private:
    // The vertices that make up this polygon,
    // either in clockwise or counter-clockwise order
    vector<Point> _vertices;
};

} // namespace utils