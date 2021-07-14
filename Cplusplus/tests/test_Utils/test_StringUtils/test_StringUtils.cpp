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
        
    QTest::newRow("Delimiter only")
        << indexer++
        << std::string("\n")
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
    std::string longPointList;
    for( int i = 0; i <= 10000;){
        longPointList += std::to_string(++i) + ' ' + std::to_string(++i) + '\n';
    }
    QTest::newRow("Looooong Point list")
        << indexer++
        << longPointList
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

        // Every time we encounter the delimiter we should split, so the resulting number of elements
        // must be one more than the number of delimiters in the original string.
        int numDelims = std::count( inputString.cbegin(), inputString.cend(), delimiter );
        QCOMPARE( out.size(), numDelims + 1 );
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
    QFETCH_GLOBAL(int, index);
    QFETCH_GLOBAL(std::string, inputString);
    QFETCH_GLOBAL(const char, subdelimiter);

    // Generic usecase
    std::pair<int,int> out1, out2;
    int x = rand();
    int y = rand();
    out1 = utils::toIntPair( std::to_string(x) + ' ' + std::to_string(y), ' ');
    out2 = std::pair<int,int>(x, y);
    QCOMPARE( out1, out2 );

    try {
        if( utils::isAnyOf( index, 0, 1, 2, 3 ) ){
            // We should expect toIntPair to throw an exception if we use an invalid format.
            QVERIFY_EXCEPTION_THROWN( utils::toIntPair(inputString, subdelimiter, out1), std::invalid_argument );
            QVERIFY_EXCEPTION_THROWN( out2 = utils::toIntPair(inputString, subdelimiter ), std::invalid_argument );
        } else {
            // Shouldn't matter which syntax we use
            utils::toIntPair(inputString, subdelimiter, out1);
            out2 = utils::toIntPair(inputString, subdelimiter);
            QCOMPARE( out1, out2 );

            // Verify order of elements in source string matches resulting pair
            auto firstPos = inputString.find(std::to_string(out1.first));
            auto delimPos = inputString.find(subdelimiter);
            auto secondPos = inputString.find(std::to_string(out1.second), firstPos);
            if( firstPos != inputString.npos
             && delimPos != inputString.npos
             && secondPos != inputString.npos ) {
                QVERIFY( firstPos < delimPos );
                QVERIFY( delimPos < secondPos );
            } else {
                // If we got here we somehow bypassed an invalid format, and we should have crashed earlier
                QFAIL("inputString has invalid format, we should have caught an exception.");
            }
        }
    } catch( const std::invalid_argument& ia ) {
        QFAIL( ia.what() );
    } catch( const std::out_of_range& oor ) {
        QFAIL( oor.what() );
    } catch( const std::exception& err ) {
        QFAIL( err.what() );
    }
}

void
TestStringUtils::subSplitToStrings()
{
    QFETCH_GLOBAL(int, index);
    QFETCH_GLOBAL(std::string, inputString);
    QFETCH_GLOBAL(const char, delimiter);
    QFETCH_GLOBAL(const char, subdelimiter);

    std::vector<std::string> out;
    try {
        // Splitting to substrings should work for any valid std::string
        if( false /* utils::isAnyOf( index, 0, 1, 2, 3 ) */ ){
        } else {
            utils::subSplit(inputString, delimiter, subdelimiter, out);

            // An empty input should be the only element of out
            if( inputString.empty() ) {
                QVERIFY( ( !out.empty() && out.at(0) == inputString ) );
            } else {
                // For all other cases, we should find each item in order within the source string
                std::string::size_type pos = 0;
                for( auto item : out ){
                    pos = inputString.find( item, pos );
                    if( pos == inputString.npos ) {
                        QFAIL((item + " not found in inputString").c_str());
                    }
                }
            }
        }
    } catch( const std::invalid_argument& ia ) {
        QFAIL( ia.what() );
    } catch( const std::out_of_range& oor ) {
        QFAIL( oor.what() );
    } catch( const std::exception& err ) {
        QFAIL( err.what() );
    }
}

void
TestStringUtils::subSplitToIntPairs()
{

    QFETCH_GLOBAL(int, index);
    QFETCH_GLOBAL(std::string, inputString);
    QFETCH_GLOBAL(const char, delimiter);
    QFETCH_GLOBAL(const char, subdelimiter);

    std::vector<std::pair<int,int>> out;
    try {
        if( false /* utils::isAnyOf( index, 0, 1, 2, 3 ) */ ){
        } else {
            utils::subSplit(inputString, delimiter, subdelimiter, out);

            // An empty input should be the only element of out
            if( inputString.empty() ) {
                QVERIFY( ( !out.empty() && out.at(0) == utils::toIntPair( inputString, subdelimiter ) ) );
            } else {
                // For all other cases, we should find each item in order within the source string
                std::string::size_type pos = 0;
                for( auto item : out ){
                    //TODO: How to check validity? find each element in order and verify exceptions thrown for invalid format?
                }
            }
        }
    } catch( const std::invalid_argument& ia ) {
        QFAIL( ia.what() );
    } catch( const std::out_of_range& oor ) {
        QFAIL( oor.what() );
    } catch( const std::exception& err ) {
        QFAIL( err.what() );
    }
}

// ----------------------------------------------------------------------------
QTEST_MAIN(TestStringUtils)
// ----------------------------------------------------------------------------