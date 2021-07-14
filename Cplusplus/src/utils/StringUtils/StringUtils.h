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

// Replaces the content of out with the substrings separated by delimiter in str.
// For example: if str = "abc,def" and delimiter = ',', the result will be ["abc", "def"]
// note that if there are no delimiters in str, the first and only element of out will just be str.
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
// Converts a string of ints to a pair of ints, we assume the format "whitespaces|first|delimiter|second|whatever"
// Will discard any additional characters after the first valid pair
void
toIntPair(const string& str, const char delimiter, pair<int,int>& out);
// Same as toIntPair(str, delimiter, out), but with different syntax
pair<int,int>
toIntPair( const string& str, const char delimiter );

} // namespace utils