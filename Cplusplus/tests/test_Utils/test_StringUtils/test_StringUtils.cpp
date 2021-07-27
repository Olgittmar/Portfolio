// Std
#include <algorithm>
#include <ranges>
#include <random>
// Own
#include <test_StringUtils.h>

#define LARGE_NUM_POINTS 10000

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
    QTest::addColumn<MYTESTS>("index");
    QTest::addColumn<std::string>("inputString");
    QTest::addColumn<const char>("delimiter");
    QTest::addColumn<const char>("subdelimiter");
    auto me = QMetaEnum::fromType<MYTESTS>();
    
    QTest::newRow(me.valueToKey( Empty ))
        << Empty // index
        << std::string() // inputString
        << '\n' // delimiter
        << ' '; // subdelimiter
    
    QTest::newRow(me.valueToKey( Invalid ))
        << Invalid
        << std::string("\n\t0 -x&<string>\"fisk\n")
        << '\n'
        << ' ';
        
    QTest::newRow(me.valueToKey( DelimOnly ))
        << DelimOnly
        << std::string("\n")
        << '\n'
        << ' ';
    
    QTest::newRow(me.valueToKey( ExtraWhitespace ))
        << ExtraWhitespace
        << std::string("\n\t\t          2 3           \t\t\t\t\n\n")
        << '\n'
        << ' ';
    
    QTest::newRow(me.valueToKey( Invalid_termination ))
        << Invalid_termination
        << std::string("1 2\n3 4\0\n5 6")
        << '\n'
        << ' ';
    
    QTest::newRow(me.valueToKey( Point ))
        << Point
        << std::string("2 3")
        << '\n'
        << ' ';
    
    QTest::newRow(me.valueToKey( PointList ))
        << PointList
        << std::string("1 2\n3 4\n5 6")
        << '\n'
        << ' ';
        
    QTest::newRow(me.valueToKey( PointList_W_Non_Std_Delim ))
        << PointList_W_Non_Std_Delim
        << std::string("1,2\t3,4\t5,6")
        << '\t'
        << ',';

    // Most elegant and compact way I could come up with to generate a string from a pattern
    // Should be possible to generate as constexpr with ranges/views, but couldn't wrap my head around it.
    std::string lpl = std::to_string(utils::randInt()) + ' ' + std::to_string(utils::randInt());
    for( int i = 2; i <= LARGE_NUM_POINTS; ++i ){
        lpl += '\n' + std::to_string(utils::randInt()) + ' ' + std::to_string(utils::randInt());
    }
    QTest::newRow( me.valueToKey( LongPointList ))
        << LongPointList
        << lpl
        << '\n'
        << ' ';
}

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------

void
TestStringUtils::split()
{
    QFETCH_GLOBAL(MYTESTS, index);
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
    QFETCH_GLOBAL(MYTESTS, index);
    QFETCH_GLOBAL(std::string, inputString);
    QFETCH_GLOBAL(const char, subdelimiter);

    // Generic usecase
    std::pair<int,int> out1, out2;
    int x = utils::randInt();
    int y = utils::randInt();
    out1 = utils::toIntPair( std::to_string(x) + ' ' + std::to_string(y), ' ');
    out2 = std::pair<int,int>(x, y);
    QCOMPARE( out1, out2 );

    try {
        if( utils::isAnyOf( index, Empty, Invalid, DelimOnly, ExtraWhitespace ) ){
            // We should expect toIntPair to throw an exception if we use an invalid format.
            // Note that InvalidTermination shouldn't throw an error, since we expect it to behave differently
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
    QFETCH_GLOBAL(MYTESTS, index);
    QFETCH_GLOBAL(std::string, inputString);
    QFETCH_GLOBAL(const char, delimiter);
    QFETCH_GLOBAL(const char, subdelimiter);

    std::vector<std::string> out;
    try {
        // Splitting to substrings should work for any valid std::string
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
    QFETCH_GLOBAL(MYTESTS, index);
    QFETCH_GLOBAL(std::string, inputString);
    QFETCH_GLOBAL(const char, delimiter);
    QFETCH_GLOBAL(const char, subdelimiter);

    std::vector<std::pair<int,int>> out;
    try {
        if( utils::isAnyOf( index, Empty, Invalid, DelimOnly, ExtraWhitespace ) ){
            // Should throw 'invalid stoi argument' exception on the same premise as toIntPair
            // eg, numbers must be convertible to int and come in the order number->subdelimiter->number->delimiter->...
            QVERIFY_EXCEPTION_THROWN( utils::subSplit(inputString, delimiter, subdelimiter, out), std::invalid_argument );
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