#pragma once
// Std
#include <string>
// Qt
#include <QTest>
// Own
#include <StringUtils.h>
#include <utils.h>

class TestStringUtils: public QObject
{
  Q_OBJECT
  public:
    enum MYTESTS {
    Empty, Invalid,
    DelimOnly, ExtraWhitespace,
    Invalid_termination, Point, PointList,
    PointList_W_Non_Std_Delim,
    LongPointList
    };
    Q_ENUM(MYTESTS);

  private slots:
    void initTestCase_data();

    // Should take a string and return a vector of strings where the elements are
    // the substrings partitioned by a delimiter
    void split();
    // Takes a string with the format "<*><intConvertible><delimiter><intConvertible><**>"
    // where * can be anything except delimiter or something convertible to int
    // and ** can be anything
    // Note that for the tests the delimiter used in toIntPair is called subdelimiter,
    // mainly so we can reuse the same data for the subsplit functions below
    void toIntPair();
    // Should take a string, split it by delimiter, then split each substring by subdelimiter
    void subSplitToStrings();
    void subSplitToIntPairs();

    void cleanupTestCase();
};