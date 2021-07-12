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
  private slots:
    void initTestCase_data();

    void split();
    void toIntPair();
    void strToIntPair();
    void subSplitToStrings();
    void subSplitToIntPairs();

    void cleanupTestCase();
};