#pragma once

// std
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
// #include <algorithm>

namespace utils {

// Replaces the content of out with the substrings separated by delimiter in str.
// For example: if str = "abc,def" and delimiter = ',', the result will be ["abc", "def"]
// note that if there are no delimiters in str, the first and only element of out will just be str.
void
split( const std::string& str, const char delimiter, std::vector<std::string>& out );
// Splits input string into substrings separated by delimiter,
// then splits each substring into substrings separated by subdelimiter,
// returns all subitems in order in a vector.
void
subSplit( const std::string& str, const char delimiter, const char subDelimiter, std::vector<std::string>& out);
// Splits input string into substrings separated by delimiter,
// then splits each substrings into pairs of ints and returns the resulting vector of pairs.
void
subSplit( const std::string& str, const char delimiter, const char subDelimiter, std::vector<std::pair<int, int>>& out );
// Converts a string of ints to a pair of ints, we assume the format "whitespaces|first|delimiter|second|whatever"
// Will discard any additional characters after the first valid pair
void
toIntPair(const std::string& str, const char delimiter, std::pair<int,int>& out);
// Same as toIntPair(str, delimiter, out), but with different syntax
std::pair<int,int>
toIntPair( const std::string& str, const char delimiter );

} // namespace utils