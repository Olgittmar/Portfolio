// Std
#include <random>
#include <algorithm>
#include <ranges>
#include <sstream>
// Own
#include <test_PointInPolygon.h>
// Qt
#include <QPainter>

// ----------------------------------------------------------------------------
// TEST INTERNALS
// ----------------------------------------------------------------------------

std::string
TestPointInPolygon::strDiff( const std::string& str1, const std::string& str2 ) const
{
    std::string diff1, diff2;
    auto it1 = str1.cbegin();
    auto it2 = str2.cbegin();
    while( it1 != str1.cend() && it2 != str2.cend() ){
        if( *it1 != *it2 ){
            diff1 += *it1;
            diff2 += *it2;
        }
        ++it1;
        ++it2;
    }
    if( it1 == str1.cend() && it2 != str2.cend() ){
        diff2 += std::string(it2, str2.cend());
    }
    if( it1 != str1.cend() && it2 == str2.cend() ){
        diff1 += std::string(it1, str1.cend());
    }
    return (diff1 + "\n\t!=\n" + diff2);
}

std::string
TestPointInPolygon::strDiffFormattedSideBySide( const std::string& str1, const std::string& str2 ) const
{
    auto it1 = str1.cbegin();
    auto it2 = str2.cbegin();
    std::string _ret;

    while( it1 != str1.cend() && it2 != str2.cend() ){
        auto diffIt = std::mismatch( it1, str1.cend(), it2, str2.cend() );
        if(diffIt.first == str1.cend() || diffIt.second == str2.cend() ) {
            break;
        } else {
            it1 = diffIt.first;
            it2 = diffIt.second;
            _ret += '\n';
        }
        while(it1 != str1.cend() && !isspace(*it1)){
            _ret += *it1++;
        }
        _ret += '\t';
        while(it2 != str2.cend() && !isspace(*it2)){
            _ret += *it2++;
        }
    }
    if( it1 == str1.cend() && it2 != str2.cend() ){
        for(; it2 != str2.cend(); ++it2){
            if(isspace(*it2)){
                _ret += "\n-\t";
            } else {
                _ret += *it2;
            }
        }
    }
    if( it1 != str1.cend() && it2 == str2.cend() ) {
        for(; it1 != str1.cend(); ++it1){
            if(isspace(*it1)){
                _ret += "\t-\n";
            } else {
                _ret += *it1;
            }
        }
    }
    return _ret;
}

// Format for PointInPolygon input data should be something like
// [numVertices] <--- polygon 1
// V1
// V2
// ...
// Vn
// [numTestPoints] <--- points to test against polygon 1
// TP1
// TP2
// ...
// TPn
// [numVertices] <---- polygon 2
// ...
//
// Note that PointInPolygon assumes delimiter = '\n' & subdelimiter = ' '
QString
TestPointInPolygon::generatePIPTestData( bool stressTest, int maxNumPolygons, int maxNumVertices, int maxNumTestPoints)
{
    auto randPoint = []()
    {
        return utils::Point( utils::randInt(), utils::randInt() );
    };
    
    // Generates and writes a Polygon as well as testPoints to textStream with correct format.
    auto makeTestData = [maxNumVertices, maxNumTestPoints, stressTest, randPoint]( QTextStream& ts ) mutable
    {
        std::vector<utils::Point> pv( utils::randInt(3, maxNumVertices ) );

        std::generate( pv.begin(), pv.end(), randPoint );
        ts << QString::number( pv.size() ) << delim;
        for ( auto v : pv ) {
            ts << v.to_string().c_str() << delim;
        }

        pv.resize( utils::randInt(3, maxNumTestPoints ) );

        std::generate( pv.begin(), pv.end(), randPoint );
        ts << QString::number( pv.size() ) << delim;
        for ( auto v : pv ) {
            ts << v.to_string().c_str() << delim;
        }
    };

    QString ret;
    QTextStream out( &ret );
    const int numPolygons = utils::randInt( 1, maxNumPolygons );
    for( int i = 0; i <= numPolygons; ++i ){
        // Generate Polygon
        makeTestData( out );
    }
    out << '0';

    return ret;
}

// ----------------------------------------------------------------------------
// TEST MANAGEMENT
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// TEST DATA
// ----------------------------------------------------------------------------
void
TestPointInPolygon::initTestCase_data()
{
    QTest::addColumn<MYTESTS>("index");
    QTest::addColumn<QString>("testdata");
    QTest::addColumn<QString>("expected");
    QString testData, expected;
    auto me = QMetaEnum::fromType<MYTESTS>();

    QTest::newRow(me.valueToKey( Empty ))
        << Empty
        << ""
        << "";
    
    QTest::newRow(me.valueToKey( InvalidFormat ))
        << InvalidFormat
        << "\t this*/shouldn't\\work \n0"
        << "";
    
    QTest::newRow(me.valueToKey( ExtraWhitespace ))
        << ExtraWhitespace
        << "  \t \t3\n  0\t 0\n10  0\n\t0 10\n1\n 5   5\n 0\n\t"
        << "on";
    
    testData = "3\n0 0\n10 0\n0 10\n"
               "7\n4 5\n5 5\n6 5\n0 0\n0 1\n-1 5\n8 1\n"
               "5\n41 -6\n-24 -74\n-51 -6\n73 17\n-30 -34\n"
               "3\n-12 -26\n39 -8\n-16 -26\n"
               "0";
    expected = "in\non\nout\non\non\nout\nin\nout\nin\nin";
    QTest::newRow(me.valueToKey( Generic ))
        << Generic
        << testData
        << expected;
    
    testData = generatePIPTestData( true );
    expected = "";
    QTest::newRow(me.valueToKey( RandGenST ))
        << RandGenST
        << testData
        << expected;
    
    QTest::newRow(me.valueToKey( RandGenBM ))
        << RandGenBM
        << generatePIPTestData(true, 10, 1000, 100)
        << "";
}

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------
void
TestPointInPolygon::PointInPolygon()
{
    QFETCH_GLOBAL(MYTESTS, index);
    QFETCH_GLOBAL(QString, testdata);
    QFETCH_GLOBAL(QString, expected);

    try {
        std::string res;
        std::ostringstream out;
        std::istringstream in( testdata.toStdString() );
    
        if( index == RandGenBM ){
            QBENCHMARK( Solutions::PointInPolygon( in, out ) );
        } else if( utils::isAnyOf( index, InvalidFormat, ExtraWhitespace ) ){
            QVERIFY_EXCEPTION_THROWN( Solutions::PointInPolygon( in, out ), std::invalid_argument );
        } else if( index == RandGenST) {
            auto startTime = std::chrono::steady_clock::now();
            res = Solutions::PointInPolygon(in, out);
            auto stopTime = std::chrono::steady_clock::now();
            auto timeSpan= std::chrono::duration_cast<std::chrono::duration<double>>(stopTime - startTime);
            QVERIFY( !res.empty() );
            QVERIFY( timeSpan.count() < 0.25 );
        } else {
            res = Solutions::PointInPolygon( in, out );
            QCOMPARE( res.size(), expected.size() );
            QCOMPARE( out.str().size(), expected.size() );
            QVERIFY2( res == expected.toStdString(), strDiffFormattedSideBySide(res, expected.toStdString()).c_str() );
            QVERIFY2( out.str() == expected.toStdString(), strDiffFormattedSideBySide(res, expected.toStdString()).c_str() );
        }
    } catch( const std::exception& e ){
        QFAIL(e.what());
    }
}

// ----------------------------------------------------------------------------
QTEST_GUILESS_MAIN(TestPointInPolygon)
// ----------------------------------------------------------------------------