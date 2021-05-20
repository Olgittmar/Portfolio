#pragma once

// std
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
// #include <algorithm>

// Own

using namespace std;

namespace utils {

// Method from the infinite wisdom of stackOverflow: https://stackoverflow.com/a/237280
void
split( const string str, const char delimiter, vector<string>& out )
{
    istringstream iss( str );
    string item;
    while ( getline( iss, item, delimiter ) )
    {
    	out.push_back( item );
    }
    out.shrink_to_fit();
}

void
subSplit( const string str, const char delimiter, const char subDelimiter, vector<string>& out)
{
    istringstream iss( str );
    string item, subItem;
    while ( getline( iss, item, delimiter ) ) {
        while ( getline(iss, subItem, subDelimiter ) ) {
	        item += subDelimiter + subItem;
        }
    	out.push_back( item );
    }
    out.shrink_to_fit();
}

void
subSplit( const string str, const char delimiter, const char subDelimiter, vector<pair<int, int>>& out )
{
    istringstream iss( str );
    string item, subItem;
    int first, second;
    while ( getline( iss, item, delimiter ) ) {
		getline( iss, subItem, subDelimiter );
		if ( !(first = atoi( subItem.c_str() ) ) ){
	    	exception( "Failed to convert item to int." );
		}
    	getline( iss, subItem, delimiter );
    	if ( !(second = atoi( item.c_str() ) ) ){
	    	exception( "Failed to convert item to int." );
    	}
		out.emplace_back( first, second );
    }
    out.shrink_to_fit();
}

void
toIntPair(const string str, const char delimiter, pair<int,int>& out)
{
    istringstream iss( str );
    string item;
    getline( iss, item, delimiter );
    if ( !(out.first = atoi( item.c_str() ) ) ){
	    exception( "Failed to convert item to int." );
    }
    getline( iss, item, delimiter );
    if ( !(out.second = atoi( item.c_str() ) ) ){
	    exception( "Failed to convert item to int." );
    }
}

//TODO Double check that we don't create a bunch of copies
pair<int,int>
strToIntPair( const string str, const char delimiter )
{
    pair<int, int> _ret;
    toIntPair( str, delimiter, _ret );
    return _ret;
}

} // namespace utils