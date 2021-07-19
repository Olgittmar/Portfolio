// Own
#include "StringUtils.h"
#include <utils.h>

namespace utils {

void
split( const std::string& str, const char delimiter, std::vector<std::string>& out )
{
    out.clear();
    out.reserve( str.size() );
    std::istringstream iss(str);
    std::string item;
    while( !iss.fail() && !iss.eof() ) {
        getline( iss, item, delimiter );
    	out.push_back( item );
    }
    out.shrink_to_fit();
}

void
subSplit( const std::string& str, const char delimiter, const char subDelimiter, std::vector<std::string>& out)
{
    out.clear();
    out.reserve( str.size() );
    std::istringstream iss( str );
    std::istringstream subiss;
    std::string item, subItem;
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
subSplit( const std::string& str, const char delimiter, const char subDelimiter, std::vector<std::pair<int, int>>& out )
{
    out.clear();
    out.reserve(str.size());
    std::istringstream iss( str );
    std::string item;
    std::pair<int,int> subItem;
    while ( !iss.fail() && !iss.eof() ) {
        getline( iss, item, delimiter );
        toIntPair( item, subDelimiter, subItem );
		out.push_back( subItem );
    }
    out.shrink_to_fit();
}

void
toIntPair(const std::string& str, const char delimiter, std::pair<int,int>& out)
{
    std::istringstream iss( str );
    std::string item;
    getline( iss, item, delimiter );
    out.first = stoi( item );
    getline( iss, item, delimiter );
    out.second = stoi( item );
}

//// Double check that we don't create a bunch of copies
// We won't if the compiler uses return value optimization properly
std::pair<int,int>
toIntPair( const std::string& str, const char delimiter )
{
    std::pair<int, int> _ret;
    toIntPair( str, delimiter, _ret );
    return _ret;
}

}