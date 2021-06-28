// Own
#include <test_Line.h>

// -----------------------------------------------------------------------
// Test data
// -----------------------------------------------------------------------
void
TestLine::initTestCase_data()
{
    QTest::addColumn<utils::Line>("line");
    QTest::addColumn<utils::Point>("start");
    QTest::addColumn<utils::Point>("end");
    utils::Point downLeft(-1,-1);
    utils::Point downRight(1,-1);
    utils::Point upLeft(-1, 1);
    utils::Point upRight(1, 1);
    QTest::addRow("default") << utils::Line() << utils::Point() << utils::Point();
    QTest::addRow("Diagonal with slope Quadrant = 1")
        << utils::Line(downLeft, upRight) << downLeft << upRight;
    QTest::addRow("Diagonal with slope Quadrant = 2")
        << utils::Line(downRight, upLeft) << downRight << upLeft;
    QTest::addRow("Diagonal with slope Quadrant = 3")
        << utils::Line(upRight, downLeft) << upRight << downLeft;
    QTest::addRow("Diagonal with slope Quadrant = 4")
        << utils::Line(upLeft, downRight) << upLeft << downRight;
    QTest::addRow("Horizontal")
        << utils::Line( -1, 0, 1, 0 ) << utils::Point(-1, 0) << utils::Point(1, 0);
    QTest::addRow("Vertical")
        << utils::Line( 0, -1, 0, 1 ) << utils::Point(0, -1) << utils::Point(0, 1);
}

void
TestLine::inHRange_data()
{
    QFETCH_GLOBAL(utils::Line, line);
    QTest::addColumn<utils::Line>("theLine");
    QTest::addColumn<utils::Point>("extPoint");
    QTest::addColumn<bool>("expected");

    QTest::addRow("aboveLine")     << line << utils::Line::aboveLine(line)     << true;
    QTest::addRow("belowLine")     << line << utils::Line::belowLine(line)     << true;
    QTest::addRow("leftOfLine")    << line << utils::Line::leftOfLine(line)    << false;
    QTest::addRow("rightOfLine")   << line << utils::Line::rightOfLine(line)   << false;
    QTest::addRow("aboveMidpoint") << line << utils::Line::aboveMidpoint(line) << true;
    QTest::addRow("belowMidpoint") << line << utils::Line::belowMidpoint(line) << true;
    if( qAbs(line.end().x() - line.start().x()) >= 2 ){
        QTest::addRow("leftOfMidpoint")  << line << utils::Line::leftOfMidpoint(line)  << true;
        QTest::addRow("rightOfMidpoint") << line << utils::Line::rightOfMidpoint(line) << true;
    } else {
        QTest::addRow("leftOfMidpoint")  << line << utils::Line::leftOfMidpoint(line)  << false;
        QTest::addRow("rightOfMidpoint") << line << utils::Line::rightOfMidpoint(line) << false;
    }
}

void
TestLine::inVRange_data()
{
    QFETCH_GLOBAL(utils::Line, line);
    QTest::addColumn<utils::Line>("theLine");
    QTest::addColumn<utils::Point>("extPoint");
    QTest::addColumn<bool>("expected");

    QTest::addRow("aboveLine")   << line << utils::Line::aboveLine(line)   << false;
    QTest::addRow("belowLine")   << line << utils::Line::belowLine(line)   << false;
    QTest::addRow("leftOfLine")  << line << utils::Line::leftOfLine(line)  << true;
    QTest::addRow("rightOfLine") << line << utils::Line::rightOfLine(line) << true;
    if( qAbs(line.end().y() - line.start().y()) >= 2 ){
        QTest::addRow("aboveMidpoint") << line << utils::Line::aboveMidpoint(line) << true;
        QTest::addRow("belowMidpoint") << line << utils::Line::belowMidpoint(line) << true;
    } else {
        QTest::addRow("aboveMidpoint") << line << utils::Line::aboveMidpoint(line) << false;
        QTest::addRow("belowMidpoint") << line << utils::Line::belowMidpoint(line) << false;
    }
    QTest::addRow("leftOfMidpoint")  << line << utils::Line::leftOfMidpoint(line)  << true;
    QTest::addRow("rightOfMidpoint") << line << utils::Line::rightOfMidpoint(line) << true;
}

void
TestLine::intersects_data()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    QTest::addColumn<utils::Line>("theLine");
    QTest::addColumn<utils::Point>("extPoint");
    QTest::addColumn<bool>("expected");

    QTest::addRow("start") << line << start << true;
    QTest::addRow("end") << line << end << true;
    QTest::addRow("aboveLine") << line << utils::Line::aboveLine(line) << false;
    QTest::addRow("belowLine") << line << utils::Line::belowLine(line) << false;
    QTest::addRow("leftOfLine") << line << utils::Line::leftOfLine(line) << true;
    QTest::addRow("rightOfLine") << line << utils::Line::rightOfLine(line) << false;
    
    QTest::addRow("leftOfMidPoint") << line << utils::Line::leftOfMidpoint(line) << true;
    if( start.y() == end.y() && qAbs( end.x() - start.x() ) >= 2 ){
        QTest::addRow("rightOfMidPoint") << line << utils::Line::rightOfMidpoint(line) << true;
    } else {
        QTest::addRow("rightOfMidPoint") << line << utils::Line::rightOfMidpoint(line) << false;
    }
    
    switch( line.slopeQuadrant() ){
    case 1:
    case 3:
    {
        QTest::addRow("aboveMidPoint") << line << utils::Line::aboveMidpoint(line) << true;
        QTest::addRow("belowMidPoint") << line << utils::Line::belowMidpoint(line) << false;
    }
    break;
    case 2:
    case 4:
    {
        QTest::addRow("aboveMidPoint") << line << utils::Line::aboveMidpoint(line) << false;
        QTest::addRow("belowMidPoint") << line << utils::Line::belowMidpoint(line) << true;
    }
    break;
    case 0:
    default:
    {
        if( start.x() == end.x() && qAbs(end.y() - start.y()) >= 2 ){
            QTest::addRow("aboveMidPoint") << line << utils::Line::aboveMidpoint(line) << true;
            QTest::addRow("belowMidPoint") << line << utils::Line::belowMidpoint(line) << true;
        } else {
            QTest::addRow("aboveMidPoint") << line << utils::Line::aboveMidpoint(line) << false;
            QTest::addRow("belowMidPoint") << line << utils::Line::belowMidpoint(line) << false;
        }
    }
    }
}

void
TestLine::includes_data()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    QTest::addColumn<utils::Line>("theLine");
    QTest::addColumn<utils::Point>("extPoint");
    QTest::addColumn<bool>("expected");

    QTest::addRow("start") << line << start << true;
    QTest::addRow("end") << line << end << true;
    QTest::addRow("midpoint") << line << line.midpoint() << true;

    QTest::addRow("aboveLine")       << line << utils::Line::aboveLine(line) << false;
    QTest::addRow("belowLine")       << line << utils::Line::belowLine(line) << false;
    QTest::addRow("leftOfLine")      << line << utils::Line::leftOfLine(line) << false;
    QTest::addRow("rightOfLine")     << line << utils::Line::rightOfLine(line) << false;

    if( line.isAngled() || start == end ){
        QTest::addRow("aboveMidPoint")   << line << utils::Line::aboveMidpoint(line) << false;
        QTest::addRow("belowMidPoint")   << line << utils::Line::belowMidpoint(line) << false;
        QTest::addRow("leftOfMidPoint")  << line << utils::Line::leftOfMidpoint(line) << false;
        QTest::addRow("rightOfMidPoint") << line << utils::Line::rightOfMidpoint(line) << false;
    } else if( start.y() == end.y() ) {
        QTest::addRow("aboveMidPoint")   << line << utils::Line::aboveMidpoint(line) << false;
        QTest::addRow("belowMidPoint")   << line << utils::Line::belowMidpoint(line) << false;
        if( qAbs( end.x() - start.x() ) >= 2 ){
            QTest::addRow("leftOfMidPoint")  << line << utils::Line::leftOfMidpoint(line) << true;
            QTest::addRow("rightOfMidPoint") << line << utils::Line::rightOfMidpoint(line) << true;
        } else {
            QTest::addRow("leftOfMidPoint")  << line << utils::Line::leftOfMidpoint(line) << false;
            QTest::addRow("rightOfMidPoint") << line << utils::Line::rightOfMidpoint(line) << false;        
        }
    } else {
        QTest::addRow("leftOfMidPoint")  << line << utils::Line::leftOfMidpoint(line) << false;
        QTest::addRow("rightOfMidPoint") << line << utils::Line::rightOfMidpoint(line) << false;
        if( qAbs( end.y() - start.y() ) >= 2 ){
            QTest::addRow("aboveMidPoint")   << line << utils::Line::aboveMidpoint(line) << true;
            QTest::addRow("belowMidPoint")   << line << utils::Line::belowMidpoint(line) << true;
        } else {
            QTest::addRow("aboveMidPoint")   << line << utils::Line::aboveMidpoint(line) << false;
            QTest::addRow("belowMidPoint")   << line << utils::Line::belowMidpoint(line) << false;
        }
    }
}

// -----------------------------------------------------------------------
// Test cases
// -----------------------------------------------------------------------
void
TestLine::internalPointsInitialized()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    
    QCOMPARE(line.start(), start);
    QCOMPARE(line.end(), end);
    QCOMPARE(line.midpoint(),
        utils::Point(
            start.x() + qRound((double)(end.x() - start.x())/2.0),
            start.y() + qRound((double)(end.y() - start.y())/2.0) ));
}

void
TestLine::aboveLine()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    
    utils::Point p = utils::Line::aboveLine(line);
    QVERIFY( p.y() > start.y() );
    QVERIFY( p.y() > end.y() );
    QVERIFY( p.x() >= qMin(start.x(), end.x()) );
    QVERIFY( p.x() <= qMax(start.x(), end.x()) );
}

void
TestLine::belowLine()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    utils::Point p = utils::Line::belowLine( line );
    QVERIFY( p.y() < start.y() );
    QVERIFY( p.y() < end.y() );
    QVERIFY( p.x() >= qMin(start.x(), end.x()) );
    QVERIFY( p.x() <= qMax(start.x(), end.x()) );
}

void
TestLine::leftOfLine()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    utils::Point p = utils::Line::leftOfLine( line );
    QVERIFY( p.x() < start.x() );
    QVERIFY( p.x() < end.x() );
    QVERIFY( p.y() >= qMin(start.y(), end.y()) );
    QVERIFY( p.y() <= qMax(start.y(), end.y()) );
}

void
TestLine::rightOfLine()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    utils::Point p = utils::Line::rightOfLine( line );
    QVERIFY( p.x() > start.x() );
    QVERIFY( p.x() > end.x() );
    QVERIFY( p.y() >= qMin(start.y(), end.y()) );
    QVERIFY( p.y() <= qMax(start.y(), end.y()) );
}

void
TestLine::aboveMidpoint()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    
    utils::Point p = utils::Line::aboveMidpoint(line);
    QVERIFY( p.y() > line.midpoint().y() );
    QVERIFY( p.x() >= qMin(start.x(), end.x()) );
    QVERIFY( p.x() <= qMax(start.x(), end.x()) );
}

void
TestLine::belowMidpoint()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    
    utils::Point p = utils::Line::belowMidpoint(line);
    QVERIFY( p.y() < line.midpoint().y() );
    QVERIFY( p.x() >= qMin(start.x(), end.x()) );
    QVERIFY( p.x() <= qMax(start.x(), end.x()) );
}

void
TestLine::leftOfMidpoint()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    
    utils::Point p = utils::Line::leftOfMidpoint(line);
    QVERIFY( p.x() < line.midpoint().x() );
    QVERIFY( p.y() >= qMin(start.y(), end.y()) );
    QVERIFY( p.y() <= qMax(start.y(), end.y()) );
}

void
TestLine::rightOfMidpoint()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);
    
    utils::Point p = utils::Line::rightOfMidpoint(line);
    QVERIFY( p.x() > line.midpoint().x() );
    QVERIFY( p.y() >= qMin(start.y(), end.y()) );
    QVERIFY( p.y() <= qMax(start.y(), end.y()) );
}

void
TestLine::slope()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    double dx = end.x() - start.x();
    double dy = end.y() - start.y();
    if(dx == 0){
        QVERIFY(line.slope() == INFINITY);
    } else if(dy == 0){
        QVERIFY(line.slope() == 0.0);
    } else {
        QCOMPARE(line.slope(), dy/dx );
    }
}

void
TestLine::invSlope()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    double dy = end.y() - start.y();
    double dx = end.x() - start.x();
    if(dy == 0){
        QVERIFY(line.invSlope() == INFINITY);
    } else if(dx == 0){
        QVERIFY(line.invSlope() == 0.0);
    } else {
        QCOMPARE(line.invSlope(), dx/dy );
    }
}

void
TestLine::slopeQuadrant()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    double dy = end.y() - start.y();
    double dx = end.x() - start.x();
    if( dx > 0 && dy > 0 ){
        QCOMPARE( line.slopeQuadrant(), 1 );
    } else if( dx < 0 && dy > 0 ){
        QCOMPARE( line.slopeQuadrant(), 2 );
    } else if( dx < 0 && dy < 0 ){
        QCOMPARE( line.slopeQuadrant(), 3 );
    } else if( dx > 0 && dy < 0 ){
        QCOMPARE( line.slopeQuadrant(), 4 );
    } else {
        QVERIFY(line.slopeQuadrant() == 0);
    }
}

void
TestLine::isAngled()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    double dy = end.y() - start.y();
    double dx = end.x() - start.x();
    QVERIFY( ( dx == 0 || dy == 0 ) != line.isAngled() );
}

void
TestLine::inHRange()
{
    QFETCH(utils::Line, theLine);
    QFETCH(utils::Point, extPoint);
    QFETCH(bool, expected);

    QTRY_COMPARE( theLine.inHRange( extPoint.x() ), expected);
}

void
TestLine::inVRange()
{
    QFETCH(utils::Line, theLine);
    QFETCH(utils::Point, extPoint);
    QFETCH(bool, expected);

    QCOMPARE( theLine.inVRange( extPoint.y() ), expected);
}

void
TestLine::yAt()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    if( start.x() == end.x() ){
        QVERIFY_EXCEPTION_THROWN( line.yAt( start.x() ), std::exception );
    } else {
        QCOMPARE( line.yAt( start.x() ), start.y() );
        QCOMPARE( line.yAt( end.x() ), end.y() );
        QCOMPARE( line.yAt( line.midpoint().x() ), line.midpoint().y() );
        
        int minX = qMin( start.x(), end.x() ) - 11;
        int maxX = qMax( start.x(), end.x() ) + 11;
        int minY = qMin( start.y(), end.y() );
        int maxY = qMax( start.y(), end.y() );
        switch( line.slopeQuadrant() ){
        case 1:
        case 3:
        {
            QVERIFY( line.yAt( minX ) < minY );
            QVERIFY( line.yAt( maxX ) > maxY );
        }
        break;
        case 2:
        case 4:
        {
            QVERIFY( line.yAt( minX ) > maxY );
            QVERIFY( line.yAt( maxX ) < minY );
        }
        break;
        case 0:
        default:
        {
            QCOMPARE( line.yAt( minX ), start.y() );
            QCOMPARE( line.yAt( maxX ), start.y() );
        }
        }
    }
}

void
TestLine::xAt()
{
    QFETCH_GLOBAL(utils::Line, line);
    QFETCH_GLOBAL(utils::Point, start);
    QFETCH_GLOBAL(utils::Point, end);

    if( start.y() == end.y() ){
        QVERIFY_EXCEPTION_THROWN( line.xAt( start.y() ), std::exception );
    } else {
        QCOMPARE( line.xAt( start.y() ), start.x() );
        QCOMPARE( line.xAt( end.y() ), end.x() );
        QCOMPARE( line.xAt( line.midpoint().y() ), line.midpoint().x() );

        int minY = qMin( start.y(), end.y() ) - 11;
        int maxY = qMax( start.y(), end.y() ) + 11;
        int minX = qMin( start.x(), end.x() );
        int maxX = qMax( start.x(), end.x() );
        switch( line.slopeQuadrant() ){
        case 1:
        case 3:
        {
            QVERIFY( line.xAt( minY ) < minX );
            QVERIFY( line.xAt( maxY ) > maxX );
        }
        break;
        case 2:
        case 4:
        {
            QVERIFY( line.xAt( minY ) > maxX );
            QVERIFY( line.xAt( maxY ) < minX );
        }
        break;
        case 0:
        default:
        {
            QCOMPARE( line.xAt( minY ), start.x() );
            QCOMPARE( line.xAt( maxY ), start.x() );
        }
        }
    }
}

void
TestLine::intersects()
{
    QFETCH(utils::Line, theLine);
    QFETCH(utils::Point, extPoint);
    QFETCH(bool, expected);

    QCOMPARE( theLine.intersects( extPoint ), expected );
}

void
TestLine::includes()
{
    QFETCH(utils::Line, theLine);
    QFETCH(utils::Point, extPoint);
    QFETCH(bool, expected);

    QCOMPARE( theLine.includes( extPoint ), expected );
}

// -----------------------------------------------------------------------
QTEST_MAIN(TestLine)
// -----------------------------------------------------------------------