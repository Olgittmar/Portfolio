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

void
TestPolygon::initTestCase_data()
{
    QTest::addColumn<utils::Polygon>("polygon");

    QTest::newRow("Empty") << utils::Polygon();
    QTest::newRow("Q1 triangle")
        << utils::Polygon({
            utils::Point(0,0),
            utils::Point(0,10),
            utils::Point(10,0)
        });
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

}

// --------------------------------------------------------------------------
QTEST_MAIN(TestPolygon)
// --------------------------------------------------------------------------