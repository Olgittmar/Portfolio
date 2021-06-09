#include <catch2/catch.hpp>
#include <Line.h>
#include <Point.h>

using namespace utils;

//TODO I don't like this test structure, it isn't readable. It generates the lines and points over and over when we could be reusing them.
// Will probably get back to this further down the line, but for now it does the job.
TEST_CASE( "Line initialization", "[Line]" ) {
    using namespace utils;
    int start_x = GENERATE(-1, 0, 1);
    int start_y = GENERATE(-1, 0, 1);
    int end_x =   GENERATE(-1, 0, 1);
    int end_y =   GENERATE(-1, 0, 1);

    Point start( start_x, start_y);
    Point end( end_x, end_y );

    REQUIRE_NOTHROW( Line( start, end ) );
    REQUIRE_NOTHROW( Line( start.x(), start.y(), end.x(), end.y() ) );
    std::string inputstr = std::to_string( start.x() ) + " " + std::to_string( start.y() ) + "\n"
                         + std::to_string( end.x() ) + " " + std::to_string( end.y() );
    REQUIRE_NOTHROW( Line( inputstr ) );
    REQUIRE_NOTHROW( Line( start, end ).fromEnd( start ) );
    REQUIRE( Line(start, end).start() == start );
    REQUIRE( Line(start, end).end() == end );
}

TEST_CASE( "Getters for points relative to line", "[Line]" ) {
    int start_x = GENERATE(-300, -100, 0, 100, 300);
    int start_y = GENERATE(-300, -100, 0, 100, 300);
    int end_x =   GENERATE(-300, -100, 0, 100, 300);
    int end_y =   GENERATE(-300, -100, 0, 100, 300);
    Point start( start_x, start_y);
    Point end( end_x, end_y );
    Point midPoint( start_x + (int)std::round( (end_x - start_x) /2 ),
                    start_y + (int)std::round( (end_y - start_y) /2 ) );
    
    Line theLine(start, end);
    Point testPoint;
    DYNAMIC_SECTION( "for Line: " << theLine ){
		SECTION( "Line::aboveLine" ){
            testPoint = Line::aboveLine( theLine );
    		REQUIRE( testPoint.y() > max( start_y, end_y ) );
    		REQUIRE( theLine.inHRange( testPoint.x() ) );
    		REQUIRE_FALSE( theLine.inVRange( testPoint.y() ) );
    	}
    	SECTION("Line::belowLine"){
            testPoint = Line::belowLine( theLine );
    	    REQUIRE( testPoint.y() < min( start_y, end_y ) );
    	    REQUIRE( theLine.inHRange( testPoint.x() ) );
    	    REQUIRE_FALSE( theLine.inVRange( testPoint.y() ) );
    	}
	    SECTION( "Line::leftOfLine" ) {
            testPoint = Line::leftOfLine( theLine );
	        REQUIRE( testPoint.x() < min( start_x, end_x ) );
	        REQUIRE_FALSE( theLine.inHRange( testPoint.x() ) );
	        REQUIRE( theLine.inVRange( testPoint.y() ) );
	    }
	    SECTION("Line::rightOfLine"){
            testPoint = Line::rightOfLine( theLine );
	        REQUIRE( testPoint.x() > max( start_x, end_x ) );
	        REQUIRE_FALSE( theLine.inHRange( testPoint.x() ) );
	        REQUIRE( theLine.inVRange( testPoint.y() ) );
	    }
        SECTION("Line::aboveMidpoint"){
            testPoint = Line::aboveMidpoint( theLine );
    		REQUIRE( testPoint.x() == midPoint.x() );
    		REQUIRE( testPoint.y() > midPoint.y() );
    		REQUIRE( theLine.inHRange( testPoint.x() ) );
    	    if( abs(end_y - start_y) >= 2 ){
				REQUIRE( theLine.inVRange( testPoint.y() ) );
			} else {
				REQUIRE_FALSE( theLine.inVRange( testPoint.y() ) );
			}
        }
        SECTION("Line::belowMidpoint"){
            testPoint = Line::belowMidpoint( theLine );
    	    REQUIRE( testPoint.x() == midPoint.x() );
    	    REQUIRE( testPoint.y() < midPoint.y() );
    	    REQUIRE( theLine.inHRange( testPoint.x() ) );
    	    if( abs(end_y - start_y) >= 2 ){
    	        REQUIRE( theLine.inVRange( testPoint.y() ) );
    	    } else {
                REQUIRE_FALSE( theLine.inVRange( testPoint.y() ) );
    	    }
        }
        SECTION("Line::leftOfMidpoint"){
            testPoint = Line::leftOfMidpoint( theLine );
	        REQUIRE( testPoint.y() == midPoint.y() );
	        REQUIRE( testPoint.x() < midPoint.x() );
            if( abs(end_x - start_x) >= 2 ){
	            REQUIRE( theLine.inHRange( testPoint.x() ) );
            } else {
                REQUIRE_FALSE( theLine.inHRange( testPoint.x() ) );
            }
	        REQUIRE( theLine.inVRange( testPoint.y() ) );
        }
        SECTION("Line::rightOfMidpoint"){
            testPoint = Line::rightOfMidpoint( theLine );
	        REQUIRE( testPoint.y() == midPoint.y() );
	        REQUIRE( testPoint.x() > midPoint.x() );
            if( abs(end_x - start_x) >= 2 ){
	            REQUIRE( theLine.inHRange( testPoint.x() ) );
            } else {
	            REQUIRE_FALSE( theLine.inHRange( testPoint.x() ) );
            }
	        REQUIRE( theLine.inVRange( testPoint.y() ) );
        }
    }
}

TEST_CASE( "Line internal points", "[Line]" ){
   	int start_x = GENERATE(-20, -10, 0, 10, 20);
   	int start_y = GENERATE(-20, -10, 0, 10, 20);
   	int end_x =   GENERATE(-20, -10, 0, 10, 20);
   	int end_y =   GENERATE(-20, -10, 0, 10, 20);
   	Point start( start_x, start_y);
   	Point end( end_x, end_y );
   	Point midPoint( start_x + (int)std::round( (end_x - start_x) /2 ),
   	                start_y + (int)std::round( (end_y - start_y) /2 ) );
   	Line theLine(start, end);

    DYNAMIC_SECTION("Line:" << theLine << " with midpoint " << midPoint ){
	    SECTION( "Functions for internal points should return points on the line" ){
	    	REQUIRE( theLine.start() == start );
	    	REQUIRE( theLine.end() == end );
	    	REQUIRE( theLine.midpoint() == midPoint );
	    }
	    SECTION( "Internal points are in horizontal range" ){
           	REQUIRE( theLine.inHRange( start_x ) );
           	REQUIRE( theLine.inHRange( end_x ) );
           	REQUIRE( theLine.inHRange( midPoint.x() ) );
	    }
	    SECTION( "Internal points are in vertical range" ){
           	REQUIRE( theLine.inVRange( start_y ) );
           	REQUIRE( theLine.inVRange( end_y ) );
           	REQUIRE( theLine.inVRange( midPoint.y() ) );
	    }
	    SECTION( "Internal points are included" ){
           	REQUIRE( theLine.includes( start ) );
           	REQUIRE( theLine.includes( end ) );
           	REQUIRE( theLine.includes( midPoint ) );
	    }
	    SECTION( "Internal points intersects" ){
           	REQUIRE( theLine.intersects( start ) );
           	REQUIRE( theLine.intersects( end ) );
           	REQUIRE( theLine.intersects( midPoint ) );
	    }
    }
}

TEST_CASE("A horizontal line", "[Line]"){
	int start_x = GENERATE(-10, 0, 10);
	int start_y = start_x;
	int end_x = GENERATE(-5, 5, 20 );
	int end_y = start_y;
	Line theLine(start_x, start_y, end_x, end_y);
	Point midpoint( start_x + (int)round( ( end_x - start_x )/2 ),
					start_y + (int)round( ( end_y - start_y )/2 ) );
	
	REQUIRE( theLine.slope() == 0 );
	REQUIRE( isinf( theLine.invSlope() ) );
    REQUIRE( theLine.slopeQuadrant() == 0 );
    REQUIRE_FALSE( theLine.isAngled() );
	REQUIRE( theLine.yAt( start_x ) == start_y );
    REQUIRE( theLine.yAt( end_x ) == end_y );
    REQUIRE( theLine.yAt( midpoint.x() ) == midpoint.y() );
    REQUIRE_THROWS( theLine.xAt( start_y ) );
    REQUIRE_THROWS( theLine.xAt( end_y ) );
    REQUIRE_THROWS( theLine.xAt( midpoint.y() ) );
}

TEST_CASE("A vertical line", "[Line]"){
	int start_y = GENERATE( -10, 0, 10 );
	int start_x = start_y;
	int end_y = GENERATE(-5, 5, 20 );
	int end_x = start_x;
	Line theLine(start_x, start_y, end_x, end_y);
	Point midpoint( start_x + (int)round( ( end_x - start_x )/2 ),
					start_y + (int)round( ( end_y - start_y )/2 ) );
	
	REQUIRE( isinf( theLine.slope() ) );
	REQUIRE( theLine.invSlope() == 0 );
    REQUIRE( theLine.slopeQuadrant() == 0 );
    REQUIRE_FALSE( theLine.isAngled() );
	REQUIRE_THROWS( theLine.yAt( start_x ) );
    REQUIRE_THROWS( theLine.yAt( end_x ) );
    REQUIRE_THROWS( theLine.yAt( midpoint.x() ) );
    REQUIRE( theLine.xAt( start_y ) == start_x );
    REQUIRE( theLine.xAt( end_y ) == end_x );
    REQUIRE( theLine.xAt( midpoint.y() ) == midpoint.x() );
}

TEST_CASE( "A Line with start == end", "[Line]" ){
	int start_x = GENERATE(-1, 0, 1);
	int start_y = start_x;
	int end_y = start_x;
	int end_x = start_x;
	Line theLine(start_x, start_y, end_x, end_y);
	Point midpoint( start_x + (int)round( ( end_x - start_x )/2 ),
					start_y + (int)round( ( end_y - start_y )/2 ) );

	REQUIRE( theLine.slope() == INFINITY );
	REQUIRE( theLine.invSlope() == INFINITY );
	REQUIRE( theLine.slopeQuadrant() == 0 );
	REQUIRE_FALSE( theLine.isAngled() );

	REQUIRE_THROWS( theLine.yAt( start_x ) );
	REQUIRE_THROWS( theLine.xAt( start_y ) );
	REQUIRE_THROWS( theLine.yAt( end_x ) );
	REQUIRE_THROWS( theLine.xAt( end_y ) );
	REQUIRE_THROWS( theLine.yAt( midpoint.x() ) );
	REQUIRE_THROWS( theLine.xAt( midpoint.y() ) );
}

TEST_CASE( "External points with a sloped line", "[Line]" ){
    int start_x = GENERATE(-10, -5, 5, 10);
    int start_y = GENERATE(-20, -10, 10, 20);
    int end_x = -start_x;
    int end_y = -start_y;
    Line theLine(start_x, start_y, end_x, end_y);
    Point testPoint;
    
    REQUIRE_FALSE( theLine.slope() == INFINITY );
    REQUIRE_FALSE( theLine.slope() == 0 );
    REQUIRE_FALSE( theLine.invSlope() == INFINITY );
    REQUIRE_FALSE( theLine.invSlope() == 0 );
    REQUIRE_FALSE( theLine.slopeQuadrant() == 0 );
    REQUIRE( theLine.isAngled() );

    DYNAMIC_SECTION( "Line slope is in quadrant " << theLine.slopeQuadrant() ){
        SECTION("A point above the line, but within horizontal range") {
            testPoint = Line::aboveLine( theLine );
            REQUIRE( theLine.inHRange( testPoint.x() ) );
            REQUIRE_FALSE( theLine.inVRange( testPoint.y() ) );
            REQUIRE_FALSE( theLine.includes( testPoint ) );
            REQUIRE_FALSE( theLine.intersects( testPoint ) );
        }
        SECTION("A point below the line but within horizontal range") {
            testPoint = Line::belowLine( theLine );
            REQUIRE( theLine.inHRange( testPoint.x() ) );
            REQUIRE_FALSE( theLine.inVRange( testPoint.y() ) );
            REQUIRE_FALSE( theLine.includes( testPoint ) );
            REQUIRE_FALSE( theLine.intersects( testPoint ) );
        }
        SECTION("A point left of the line but within vertical range") {
            testPoint = Line::leftOfLine( theLine );
            REQUIRE_FALSE( theLine.inHRange( testPoint.x() ) );
            REQUIRE( theLine.inVRange( testPoint.y() ) );
            REQUIRE_FALSE( theLine.includes( testPoint ) );
            REQUIRE( theLine.intersects( testPoint ) );
        }
        SECTION("A point right of the line but within vertical range") {
            testPoint = Line::rightOfLine( theLine );
            REQUIRE_FALSE( theLine.inHRange( testPoint.x()) );
            REQUIRE( theLine.inVRange( testPoint.y()) );
            REQUIRE_FALSE( theLine.includes( testPoint) );
            REQUIRE_FALSE( theLine.intersects( testPoint) );
        }
        SECTION("A point left of the lines midpoint, within horizontal and vertical range"){
            testPoint = Line::leftOfMidpoint( theLine );
            REQUIRE( theLine.inVRange(testPoint.y()) );
            REQUIRE( theLine.inVRange(testPoint.y()) );
            REQUIRE_FALSE( theLine.includes(testPoint) );
            REQUIRE( theLine.intersects(testPoint) );
        }
        SECTION("A point right of the lines midpoint, within horizontal and vertical range"){
            testPoint = Line::rightOfMidpoint( theLine );
            REQUIRE( theLine.inVRange(testPoint.y()) );
            REQUIRE( theLine.inVRange(testPoint.y()) );
            REQUIRE_FALSE( theLine.includes(testPoint) );
            REQUIRE_FALSE( theLine.intersects(testPoint) );
        }
        if( (theLine.slopeQuadrant() == 1 || theLine.slopeQuadrant() == 3) ){
            SECTION("A point above the lines midpoint, within horizontal and vertical range"){
                testPoint = Line::aboveMidpoint( theLine );
                REQUIRE( theLine.inHRange(testPoint.x()) );
                REQUIRE( theLine.inVRange(testPoint.y()) );
                REQUIRE_FALSE( theLine.includes(testPoint) );
                REQUIRE( theLine.intersects(testPoint) );
            }
            SECTION("A point below the lines midpoint, within horizontal and vertical range"){
                testPoint = Line::belowMidpoint( theLine );
                REQUIRE( theLine.inVRange(testPoint.y()) );
                REQUIRE( theLine.inVRange(testPoint.y()) );
                REQUIRE_FALSE( theLine.includes(testPoint) );
                REQUIRE_FALSE( theLine.intersects(testPoint) );
            }
        }
        if( (theLine.slopeQuadrant() == 2 || theLine.slopeQuadrant() == 4) ){
            SECTION("A point above the lines midpoint, within horizontal and vertical range"){
                testPoint = Line::aboveMidpoint( theLine );
                REQUIRE( theLine.inHRange(testPoint.x()) );
                REQUIRE( theLine.inVRange(testPoint.y()) );
                REQUIRE_FALSE( theLine.includes(testPoint) );
                REQUIRE_FALSE( theLine.intersects(testPoint) );
            }
            SECTION("A point below the lines midpoint, within horizontal and vertical range"){
                testPoint = Line::belowMidpoint( theLine );
                REQUIRE( theLine.inVRange(testPoint.y()) );
                REQUIRE( theLine.inVRange(testPoint.y()) );
                REQUIRE_FALSE( theLine.includes(testPoint) );
                REQUIRE( theLine.intersects(testPoint) );
            }
        }
    }
}