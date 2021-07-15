#include <random>
#include <algorithm>
// Own
#include <test_PointInPolygon.h>
#include <utils.h>
#include <Point.h>

// ----------------------------------------------------------------------------
// TEST MANAGEMENT
// ----------------------------------------------------------------------------
void
TestPointInPolygon::initTestCase()
{
    QFETCH_GLOBAL(MYTESTS, index);
    QFETCH_GLOBAL(QString, testfile);

    // Generates a random point with x, y in [INT_MIN, INT_MAX]
    auto randPoint = [](){
        return utils::Point( utils::randInt(), utils::randInt() );
    };
    
    if( index == RandGen ){

    } else if( utils::isAnyOf( index, RandGenSS, RandGenBM ) ){

        std::vector<utils::Point> vertices;
        vertices.resize(utils::randInt(0, maxNumVertices));
        std::generate(vertices.begin(), vertices.end(), randPoint);
        
        std::vector<utils::Point> testPoints;
        testPoints.resize(utils::randInt(0, maxNumTestPoints));
        std::generate(testPoints.begin(), testPoints.end(), randPoint);
    }
}
// ----------------------------------------------------------------------------
// TEST DATA
// ----------------------------------------------------------------------------
void
TestPointInPolygon::initTestCase_data()
{
    QTest::addColumn<MYTESTS>("index");
    QTest::addColumn<QString>("testfile");
    
    QTest::newRow(qt_getEnumName( Empty ))
        << Empty
        << testdir + "/empty.in";
    QTest::newRow(qt_getEnumName( InvalidFormat ))
        << InvalidFormat
        << testdir + "/inv.in";
    QTest::newRow(qt_getEnumName( ExtraWhitespace ))
        << ExtraWhitespace
        << testdir + "/ews.in";
    QTest::newRow(qt_getEnumName( Generic ))
        << Generic
        << testdir + "/gen0.in";
    QTest::newRow(qt_getEnumName( RandGen ))
        << RandGen
        << testdir + "/gen1.in";
    QTest::newRow(qt_getEnumName( RandGenSS ))
        << RandGenSS
        << testdir + "/gen2.in";
    QTest::newRow(qt_getEnumName( RandGenBM ))
        << RandGenBM
        << testdir + "/gen3.in";
}

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
QTEST_MAIN(TestPointInPolygon)
// ----------------------------------------------------------------------------
