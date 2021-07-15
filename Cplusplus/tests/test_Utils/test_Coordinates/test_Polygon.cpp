// Qt
#include <QString>
// Std
#include <vector>
#include <utility>
#include <exception>
// Own
#include <test_Polygon.h>
// --------------------------------------------------------------------------
// TEST DATA
// --------------------------------------------------------------------------

Q_DECLARE_METATYPE(utils::Polygon)
Q_DECLARE_METATYPE(utils::Point)
Q_DECLARE_METATYPE(utils::Line)

void
TestPolygon::initTestCase_data()
{
    QTest::addColumn<MYTESTS>("index");
    QTest::addColumn<utils::Polygon>("polygon");
    QTest::addColumn<std::string>("polygonStringRepresentation");


    QTest::newRow(qt_getEnumName(Empty))
        << Empty
        << utils::Polygon()
        << std::string();
    
    QTest::newRow(qt_getEnumName(Invalid))
        << Invalid
        << utils::Polygon()
        << std::string("  \n\t,%&'<string>' fisk\0 ");

    QTest::newRow(qt_getEnumName(Unreasonably_large_Coordinates))
        << Unreasonably_large_Coordinates
        << utils::Polygon()
        << std::string( std::to_string( INT_MAX ) + "42" );

    QTest::newRow(qt_getEnumName(Q1_Triangle))
        << Q1_Triangle
        << utils::Polygon({
            utils::Point(0,0),
            utils::Point(0,10),
            utils::Point(10,0)
        })
        << std::string("0 0\n0 10\n10 0");
    
    QTest::newRow(qt_getEnumName(Q2_Triangle))
        << Q2_Triangle
        << utils::Polygon({
            utils::Point(0,0),
            utils::Point(-10,0),
            utils::Point(10,0)
        })
        << std::string("0 0\n-10 0\n10 0");
    
    QTest::newRow(qt_getEnumName(Q3_Triangle))
        << Q3_Triangle
        << utils::Polygon({
            utils::Point(0,0),
            utils::Point(0,-10),
            utils::Point(-10,0)
        })
        << std::string("0 0\n0 -10\n-10 0");
    
    QTest::newRow(qt_getEnumName(Q4_Triangle))
        << Q4_Triangle
        << utils::Polygon({
            utils::Point(0,0),
            utils::Point(10,0),
            utils::Point(0,-10)
        })
        << std::string("0 0\n10 0\n0 -10");
    
    QTest::newRow(qt_getEnumName(Upright_Square))
        << Upright_Square
        << utils::Polygon({
            utils::Point(-5,-5),
            utils::Point(-5 ,5),
            utils::Point( 5, 5),
            utils::Point( 5,-5)
        })
        << std::string("-5 -5\n-5 5\n5 5\n5 -5");
    
    QTest::newRow(qt_getEnumName(Diamond))
        << Diamond
        << utils::Polygon({
            utils::Point(-10, 0),
            utils::Point( 0, 10),
            utils::Point( 10, 0),
            utils::Point( 0,-10)
        })
        << std::string("-10 0\n0 10\n10 0\n0 -10");
    
    QTest::newRow(qt_getEnumName(Star))
        << Star
        << utils::Polygon({
            utils::Point(-7, -7),
            utils::Point( -3, -2),
            utils::Point( -10, 0),
            utils::Point( -2, 3),
            utils::Point( 0, 10),
            utils::Point( 2, 3),
            utils::Point( 10, 0),
            utils::Point( 3, -2),
            utils::Point( 7, -7),
            utils::Point( 0, -3)
        })
        << std::string(
            "-7 -7\n"
            "-3 -2\n"
            "-10 0\n"
            "-2 3\n"
            "0 10\n"
            "2 3\n"
            "10 0\n"
            "3 -2\n"
            "7 -7\n"
            "0 -3"
        );
    
}

void
TestPolygon::iteratePolygon_data()
{
    QFETCH_GLOBAL(utils::Polygon, polygon);
    QTest::addColumn<utils::Polygon>("polygon");
    QTest::addColumn<std::vector<utils::Line>>("elements");

    if( polygon.empty() ){
        QTest::newRow("") << polygon << std::vector<utils::Line>();
    } else {
        std::vector<utils::Line> lines;
        auto vertices = polygon.getVertices();
        for( auto it = vertices.cbegin(); it != vertices.cend(); ++it ){
            if( it == vertices.cend() - 1 ){
                lines.push_back( utils::Line( *it, *(vertices.cbegin()) ) );
            } else {
                lines.push_back( utils::Line( *it, *(it + 1) ) );
            }
        }
        QTest::newRow("") << polygon << lines;
    }
}

void
TestPolygon::classify_data()
{
    QFETCH_GLOBAL(utils::Polygon, polygon);
    QTest::addColumn<utils::Polygon>("polygon");
    QTest::addColumn<utils::Point>("extPoint");
    QTest::addColumn<std::string>("expected");

    std::string point_desc = "default";
    std::string expected_res = "out";
    if ( polygon.empty() ){
        QTest::newRow(("\n\tPoint: " + point_desc).c_str())
            << polygon << utils::Point() << expected_res;
    } else {
        expected_res = "on";
        for( auto line : polygon ) {
            for( auto p : { line.start(), line.midpoint(), line.end() } ){
                point_desc = p.to_string();
                QTest::newRow(("\n\tPoint: " + point_desc).c_str())
                    << polygon << p << expected_res;
            }
        }
    }
}

void
TestPolygon::operatorOstrm_data()
{
}

// --------------------------------------------------------------------------
// TESTS
// --------------------------------------------------------------------------

void
TestPolygon::initPolygon()
{
    QVERIFY( utils::Polygon().empty() );
    QCOMPARE(
        utils::Polygon("0 0\n0 10\n10 0").getVertices(),
        std::vector<utils::Point>( {
            utils::Point(0, 0),
            utils::Point(0, 10),
            utils::Point(10, 0)
        } )
    );
    QCOMPARE(
        utils::Polygon({
            utils::Point(0,0),
            utils::Point(0,10),
            utils::Point(10,0),
        }).getVertices(),
        std::vector<utils::Point>( {
            utils::Point(0, 0),
            utils::Point(0, 10),
            utils::Point(10, 0)
        } )
    );
}

void
TestPolygon::iteratePolygon()
{
    QFETCH(utils::Polygon, polygon);
    QFETCH(std::vector<utils::Line>, elements);

    try {
        int iterations = 0;
        auto polyIt = polygon.begin();
        auto eleIt = elements.begin();
        for( ; polyIt != polygon.end(); ++polyIt ){
            QCOMPARE( *polyIt, *eleIt++ );
            iterations++;
        }
        QCOMPARE( iterations, polygon.getVertices().size() );
    } catch ( std::exception& e ){
        QFAIL(e.what());
    }

    try {
        int iterations = 0;
        auto polyIt = polygon.cbegin();
        auto eleIt = elements.cbegin();
        for( ; polyIt != polygon.cend(); ++polyIt ){
            QCOMPARE( *polyIt, *eleIt++ );
        }
        QCOMPARE( iterations, polygon.getVertices().size() );
    } catch ( std::exception& e ){
        QFAIL(e.what());
    }
}

void
TestPolygon::operatorEquals()
{
    QFETCH_GLOBAL(utils::Polygon, polygon);

    utils::Polygon similar( polygon.getVertices() );

    QCOMPARE( utils::Polygon(), utils::Polygon() );
    QVERIFY( polygon == similar );
    similar.addPoint( utils::Point() );
    QVERIFY( !(polygon == similar) );
    QVERIFY( !(similar == polygon) );
}

void
TestPolygon::addPoint()
{
    utils::Polygon poly;
    QVERIFY( poly.empty() );

    utils::Point p1(2, 3);
    utils::Point p2(3, 4);
    poly.addPoint( p1 );
    QVERIFY( poly.numVertices() == 1 );
    QVERIFY( poly.getVertices().front() == p1 );
    poly.addPoint( p2 );
    QVERIFY( poly.numVertices() == 2 );
    QVERIFY( poly.getVertices().front() == p1 );
    QVERIFY( poly.getVertices().back() == p2 );

}

void
TestPolygon::clear()
{
    utils::Polygon poly({
        utils::Point(0,0),
        utils::Point(10,0),
        utils::Point(0,10)
    });
    QVERIFY( !poly.empty() );
    poly.clear();
    QVERIFY( poly.empty() );
}

void
TestPolygon::classify()
{
    QFETCH(utils::Polygon, polygon);
    QFETCH(utils::Point, extPoint);
    QFETCH(std::string, expected);

    QCOMPARE( polygon.classify(extPoint), expected );
}

void
TestPolygon::readPolygon()
{
    QFETCH_GLOBAL(utils::Polygon, polygon);
    QFETCH_GLOBAL(std::string, polygonStringRepresentation);
    try {
        QCOMPARE( utils::Polygon(polygonStringRepresentation), polygon );
    } catch( std::exception& e ) {
        QFAIL( e.what() );
    }
}

void
TestPolygon::operatorOstrm()
{
    QFETCH_GLOBAL(MYTESTS, index);
    QFETCH_GLOBAL(utils::Polygon, polygon);
    QFETCH_GLOBAL(std::string, polygonStringRepresentation);

    try {
        std::stringstream ss;
        ss << polygon;
        if ( index == Invalid || index == Unreasonably_large_Coordinates ){
            QEXPECT_FAIL("", "An invalid string will produce an empty polygon, but shouldn't crash", Continue );
        }
        QCOMPARE( ss.str(), polygonStringRepresentation);
    } catch( const std::exception& err ) {
        QFAIL( err.what() );
    }
}

// --------------------------------------------------------------------------
QTEST_MAIN(TestPolygon)
// --------------------------------------------------------------------------