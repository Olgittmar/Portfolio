#pragma once

// std
#include <string>

// Own
#include "../StringUtils/StringUtils.h"

namespace utils {
using namespace std;

class Point {
  public:
	// We use copy constructor implicitly, 
    // but I can't see any real reason to not allow the other defaults as well.
    Point() = default;
    ~Point() = default;
    Point( const int x, const int y );
    Point( const Point& other );
    explicit Point( const string& str );
    // Might want to allow implicit conversion of pairs, assuming use looks like Pair({x,y});
    explicit Point( const pair<int,int>& coords );

    inline bool operator==(const Point& other) const {
        return (this->_x == other._x && this->_y == other._y);
    };

    static vector<Point> str_to_points( const string& str, const char delimiter, const char subDelimiter );
    std::string to_string() const;

    inline int x() const { return _x; }
    inline int y() const { return _y; }

    friend ostream& operator<<(ostream& os, const Point& p);

  protected:
  private:
    int _x;
    int _y;
};

} // namespace utils