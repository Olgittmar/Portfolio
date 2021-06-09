// Catch2
#include <catch2/catch.hpp>
// Std
#include <functional>
#include <string>
// Own
#include <Point.h>

TEST_CASE( "Points can be initialized in different ways but still represent the same point.", "[Point]" ){
    int x = GENERATE( take( 10, random(-10000, 10000) ) );
    int y = GENERATE( take( 10, random(-10000, 10000) ) );
    utils::Point p1( x, y);
    utils::Point p2( std::pair<int,int>(x, y) );
    utils::Point p3( std::to_string(x) + " " + std::to_string(y) );
    utils::Point p4( y, x );
    REQUIRE( p1 == utils::Point(p1) );
    REQUIRE( p1.x() == x );
    REQUIRE( p1.y() == y );
    REQUIRE( p1 == p2 );
    REQUIRE( p1 == p3 );
    REQUIRE( p2 == p3 ); // Redundant, but I've seen wierder things go wrong
    REQUIRE_FALSE( p1 == p4 );
    REQUIRE_FALSE( p2 == p4 );
    REQUIRE_FALSE( p3 == p4 );
}

// TEST_CASE( "A vector of points can also be initialized from a string." "[Point]" ) {
//     std::vector<int> Xs = GENERATE( chunk(10, random(-10000, 10000) ) );
//     std::vector<int> Ys = GENERATE( chunk(10, random(-10000, 10000) ) );
//     std::string pointList;
//     std::vector<utils::Point> expectedResult;
//     auto Xit = Xs.cbegin();
//     auto Yit = Ys.cbegin();
//     char delim = '\n';
//     char subDelim = ' ';

//     while( Xit != Xs.cend() && Yit != Ys.cend() ){
//         pointList.append( std::to_string( *(Xit) ) + " " + std::to_string( *(Yit) ) );
//         expectedResult.push_back( utils::Point( *(Xit++), *(Yit++) ) );
//     }
//     std::string badPointList = "2 3\n3 4\n5 6\n . fisk";

//     REQUIRE( utils::Point::str_to_points( pointList, delim, subDelim ) == expectedResult );
//     REQUIRE_THROWS( utils::Point::str_to_points( badPointList, delim, subDelim ) );
// }