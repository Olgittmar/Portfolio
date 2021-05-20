#include "Point.h"

// std
#include <algorithm>

// Own
#include "StringUtils.h"

using namespace std;

namespace utils {

// Constructors
Point::Point( const int x, const int y ) :_x(x), _y(y) {}
Point::Point( const pair<int,int> coords ): _x(coords.first), _y(coords.second) {}
Point::Point( const string str ) : Point( strToIntPair(str, ' ') ) {}

// Returns a vector of Points from the delimiter-separated pairs of coordinates separated by subDelimiter.
vector<Point>
Point::str_to_points( const string str, const char delimiter, const char subDelimiter )
{
    vector<pair<int, int>> coords;
    vector<Point> out;
    subSplit( str, delimiter, subDelimiter, coords );
    out.resize( coords.size() );
    // For every coordinate, emplace the corresponding Point to out.
    transform( coords.cbegin(), coords.cend(), out.begin(),
	       []( pair<int, int> c ) { return Point( c ); } );
    return out;
}

}