#include "StringUtils.h"
#include <utils.h>

namespace utils {

void
split( const string& str, const char delimiter, vector<string>& out )
{
    out.clear();
    out.reserve( str.size() );
    istringstream iss(str);
    string item;
    while( !iss.fail() && !iss.eof() ) {
        getline( iss, item, delimiter );
    	out.push_back( item );
    }
    out.shrink_to_fit();
}

void
subSplit( const string& str, const char delimiter, const char subDelimiter, vector<string>& out)
{
    out.clear();
    out.reserve( str.size() );
    istringstream iss( str );
    istringstream subiss;
    string item, subItem;
    while ( !iss.fail() && !iss.eof() ) {
        getline( iss, item, delimiter );
        subiss.str( item );
        while ( !subiss.fail() && !subiss.eof() ) {
            getline(subiss, subItem, subDelimiter );
    	    out.push_back( subItem );
        }
    }
    out.shrink_to_fit();
}

void
subSplit( const string& str, const char delimiter, const char subDelimiter, vector<pair<int, int>>& out )
{
    out.clear();
    out.reserve(str.size());
    istringstream iss( str );
    string item;
    pair<int,int> subItem;
    while ( !iss.fail() && !iss.eof() ) {
        getline( iss, item, delimiter );
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
toIntPair( const string& str, const char delimiter )
{
    pair<int, int> _ret;
    toIntPair( str, delimiter, _ret );
    return _ret;
}

}