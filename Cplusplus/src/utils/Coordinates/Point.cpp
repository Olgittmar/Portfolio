#include "Point.h"

// std
#include <algorithm>

// Own
#include "StringUtils.h"

namespace utils {

// Constructors
Point::Point( const int x, const int y ) :_x(x), _y(y) {}
Point::Point( const pair<int,int>& coords ): _x(coords.first), _y(coords.second) {}
Point::Point( const Point& other ) : _x( other.x() ), _y( other.y() ) {}
Point::Point( const string& str ) : Point( strToIntPair(str, ' ') ) {}

// Returns a vector of Points from the delimiter-separated pairs of coordinates separated by subDelimiter.
vector<Point>
Point::str_to_points( const string& str, const char delimiter, const char subDelimiter )
{
    vector<pair<int, int>> coords;
    vector<Point> out;
    try {
        subSplit( str, delimiter, subDelimiter, coords );
        out.resize( coords.size() );
        // For every coordinate, emplace the corresponding Point in out.
        transform( coords.cbegin(), coords.cend(), out.begin(),
	           []( const pair<int, int>& c ) { return Point( c ); } );
    } catch( const std::out_of_range& oor ) {
        // TODO: add proper logging system.
        cout << oor.what() << endl;
        out.clear();
    } catch( const std::invalid_argument& iarg ){
        cout << iarg.what() << endl;
        out.clear();
    }
    return out;
}

ostream&
operator<<(ostream& os, const Point& p)
{
    os << p.to_string();
    return os;
}

std::string
Point::to_string() const
{
    return std::string( std::to_string(x()) + " "s + std::to_string(y()) );
}

}