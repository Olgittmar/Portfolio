#include "StringUtils.h"

namespace utils {

// Method for this first one from the infinite wisdom of stackOverflow: https://stackoverflow.com/a/237280
// More elegant than what I could come up with. string.split should really be a std method though...
void
split( const string& str, const char delimiter, vector<string>& out )
{
    istringstream iss( str );
    for( string item; getline( iss, item, delimiter ); ) {
    	out.push_back( item );
    }
    out.shrink_to_fit();
}

void
subSplit( const string& str, const char delimiter, const char subDelimiter, vector<string>& out)
{
    istringstream iss( str );
    string item, subItem;
    while ( getline( iss, item, delimiter ) ) {
        istringstream subiss( item );
        while ( getline(subiss, subItem, subDelimiter ) ) {
    	    out.push_back( subItem );
        }
    }
}

void
subSplit( const string& str, const char delimiter, const char subDelimiter, vector<pair<int, int>>& out )
{
    istringstream iss( str );
    string item;
    pair<int,int> subItem;
    while ( getline( iss, item, delimiter ) ) {
        toIntPair( item, subDelimiter, subItem );
		out.push_back( subItem );
    }
    out.shrink_to_fit();
}

void
toIntPair(const string& str, const char delimiter, pair<int,int>& out)
{
    istringstream iss( str );
    string item;
    getline( iss, item, delimiter );
    out.first = stoi( item );
    getline( iss, item, delimiter );
    out.second = stoi( item );
}

//// Double check that we don't create a bunch of copies
// We won't if the compiler uses return value optimization properly
pair<int,int>
strToIntPair( const string& str, const char delimiter )
{
    pair<int, int> _ret;
    toIntPair( str, delimiter, _ret );
    return _ret;
}

}