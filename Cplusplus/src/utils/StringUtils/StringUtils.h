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

void
split( const string str, const char delimiter, vector<string>& out );

void
subSplit( const string str, const char delimiter, const char subDelimiter, vector<string>& out);

void
subSplit( const string str, const char delimiter, const char subDelimiter, vector<pair<int, int>>& out );

void
toIntPair(const string str, const char delimiter, pair<int,int>& out);

pair<int,int>
strToIntPair( const string str, const char delimiter );

} // namespace utils