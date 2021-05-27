#pragma once

// std
#include <string>

// Own
#include "../StringUtils/StringUtils.h"

using namespace std;

namespace utils {

class Point {
  public:
	// We use copy constructor implicitly, 
    // but I can't see any real reason to not allow the other defaults as well.
    Point() = default;
    ~Point() = default;
    Point( const int x, const int y );
    Point( const string str );
    Point( const pair<int,int> coords );

    inline bool operator==(const Point& other) const {
        return (this->_x == other._x && this->_y == other._y);
    };

    static vector<Point> str_to_points( const string str, const char delimiter, const char subDelimiter );

    inline int x() const { return _x; }
    inline int y() const { return _y; }

  protected:
  private:
    int _x = 0;
    int _y = 0;
};

} // namespace utils