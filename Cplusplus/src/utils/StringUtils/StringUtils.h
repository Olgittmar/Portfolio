#pragma once

// std
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
// #include <algorithm>

// Own

namespace utils {
using namespace std;

// Splits input string separated by delimiter and returns items in a vector
void
split( const string& str, const char delimiter, vector<string>& out );
// Splits input string into substrings separated by delimiter,
// then splits each substring into substrings separated by subdelimiter,
// returns all subitems in order in a vector.
void
subSplit( const string& str, const char delimiter, const char subDelimiter, vector<string>& out);
// Splits input string into substrings separated by delimiter,
// then splits each substrings into pairs of ints and returns the resulting vector of pairs.
void
subSplit( const string& str, const char delimiter, const char subDelimiter, vector<pair<int, int>>& out );
// Converts a string of ints to a pair of ints.
// Will discard any additional characters after the first valid pair
void
toIntPair(const string& str, const char delimiter, pair<int,int>& out);
// Same as above, but with different syntax
pair<int,int>
strToIntPair( const string& str, const char delimiter );

} // namespace utils