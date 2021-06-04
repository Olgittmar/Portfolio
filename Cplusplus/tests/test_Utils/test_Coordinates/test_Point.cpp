#include <catch2/catch.hpp>
#include <Point.h>

#define DEFAULT_X 2
#define DEFAULT_Y 3

TEST_CASE( "Points are instansiated", "[Point]" ){
    utils::Point p1(DEFAULT_X, DEFAULT_Y);
    utils::Point p2( std::pair<int,int>(DEFAULT_X, DEFAULT_Y) );
    utils::Point p3( std::to_string( DEFAULT_X ) + " " + std::to_string( DEFAULT_Y ) );
    REQUIRE( p1.x() == DEFAULT_X );
    REQUIRE( p1.y() == DEFAULT_Y );
    REQUIRE( p1 == p2 );
    REQUIRE( p1 == utils::Point(p1) );
}