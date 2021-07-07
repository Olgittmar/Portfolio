// Own
#include <test_Point.h>
// Std
#include <string>
#include <sstream>

Q_DECLARE_METATYPE(utils::Point)

// --------------------------------------------------------------------------
// TEST DATA
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// TESTS
// --------------------------------------------------------------------------
void
TestPoint::operatorEquals()
{
    int x = 5;
    int y = 10;
    utils::Point p1(x, y);
    QVERIFY( p1 != utils::Point() );
    QCOMPARE( p1, utils::Point( x, y ) );
    QCOMPARE( p1, utils::Point( p1 ) );
    QCOMPARE( p1, utils::Point( std::to_string(x) + " " + std::to_string(y) ) );
    QCOMPARE( p1, utils::Point( std::pair<int,int>(x, y) ) );
}

void
TestPoint::str_to_points()
{
    std::string testString("2 3\n4 5\n-6 7\n8 -9");
    std::vector<utils::Point> expectedResult({
            utils::Point(2,3),
            utils::Point(4,5),
            utils::Point(-6,7),
            utils::Point(8,-9)
        });
    auto res = utils::Point::str_to_points(testString, '\n', ' ');
    QCOMPARE( res, expectedResult );
}

void
TestPoint::operatorOStrm()
{
    std::string expectedResult = "-2 3";
    std::stringstream ss;
    ss << utils::Point(-2,3);
    QCOMPARE( ss.str(), expectedResult);
}

// --------------------------------------------------------------------------
QTEST_MAIN(TestPoint)
// --------------------------------------------------------------------------
