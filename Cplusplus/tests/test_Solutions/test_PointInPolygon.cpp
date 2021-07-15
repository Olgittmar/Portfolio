// Own
#include <test_PointInPolygon.h>
#include <utils.h>

// ----------------------------------------------------------------------------
// TEST MANAGEMENT
// ----------------------------------------------------------------------------
// void
// TestPointInPolygon::initTestCase()
// {
//     // QFETCH_GLOBAL(int, index);
//     // QFETCH_GLOBAL(QString, testfile);

// }
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
