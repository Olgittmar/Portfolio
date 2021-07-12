// Std
#include <algorithm>
// Own
#include <test_StringUtils.h>


// ----------------------------------------------------------------------------
// TEST MANEGEMENT
// ----------------------------------------------------------------------------
void
TestStringUtils::cleanupTestCase()
{
    // if( QTest::currentTestFailed() ){

    // }
}
// ----------------------------------------------------------------------------
// TEST CASE DATA
// ----------------------------------------------------------------------------

void
TestStringUtils::initTestCase_data()
{
    QTest::addColumn<int>("index");
    QTest::addColumn<std::string>("inputString");
    QTest::addColumn<const char>("delimiter");
    QTest::addColumn<const char>("subdelimiter");
    int indexer = 0;

    QTest::newRow("Empty")
        << indexer++ // index
        << std::string() // inputString
        << '\n' // delimiter
        << ' '; // subdelimiter
    
    QTest::newRow("Invalid")
        << indexer++
        << std::string("\n\t0 -x&<string>\"fisk\n")
        << '\n'
        << ' ';
        
    QTest::newRow("Extra whitespaces")
        << indexer++
        << std::string("\n\t\t          2 3           \t\t\t\t\n\n")
        << '\n'
        << ' ';
    
    QTest::newRow("Invalid termination")
        << indexer++
        << std::string("1 2\n3 4\0\n5 6")
        << '\n'
        << ' ';
    
    QTest::newRow("Point")
        << indexer++
        << std::string("2 3")
        << '\n'
        << ' ';
    
    QTest::newRow("Point list")
        << indexer++
        << std::string("1 2\n3 4\n5 6")
        << '\n'
        << ' ';
        
    QTest::newRow("Point list with non-standard (sub)delimiter")
        << indexer++
        << std::string("1,2\t3,4\t5,6")
        << '\t'
        << ',';

    // special case, not yet implemented
    QTest::newRow("Looooong Point list")
        << indexer++
        << std::string()
        << '\n'
        << ' ';
}

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------

void
TestStringUtils::split()
{
    QFETCH_GLOBAL(int, index);
    QFETCH_GLOBAL(std::string, inputString);
    QFETCH_GLOBAL(const char, delimiter);
    
    try {
        std::vector<std::string> out;
        
        utils::split(inputString, delimiter, out);
        
        // If we join the resulting elements with delimiter inbetween,
        // we should end up with something identical to the original.
        std::string res;
        auto strIt = out.cbegin();
        for( ; strIt != out.cend(); ++strIt ){
            if( strIt != out.cbegin() ){
                res += delimiter;
            }
            res += *strIt;
        }
        QCOMPARE( res.c_str(), inputString.c_str() );
    } catch( const std::exception& e ) {
        QFAIL( e.what() );
    }
}

void
TestStringUtils::toIntPair()
{

}

void
TestStringUtils::strToIntPair()
{

}

void
TestStringUtils::subSplitToStrings()
{

}

void
TestStringUtils::subSplitToIntPairs()
{

}

// ----------------------------------------------------------------------------
QTEST_MAIN(TestStringUtils)
// ----------------------------------------------------------------------------