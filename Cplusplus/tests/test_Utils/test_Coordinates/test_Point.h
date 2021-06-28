#pragma once
// Qt
#include <QTest>
// Own
#include <Point.h>

// --------------------------------------------------------------------------
// TEST CLASS
// --------------------------------------------------------------------------
// Not very meaningful testClass, Point is by design really simple
// I'm also unsure how to write tests for constructors and operators...
class TestPoint: public QObject
{
    Q_OBJECT
  private slots:
    void operatorEquals();
    void str_to_points();
    void operatorOStrm();
};

// --------------------------------------------------------------------------