#pragma once
// Qt
#include <QTest>
// Own
#include <Polygon.h>

// --------------------------------------------------------------------------
// TEST CLASS
// --------------------------------------------------------------------------
class TestPolygon: public QObject
{
  Q_OBJECT
  private slots:
    void initTestCase_data();
    void classify_data();

    void initPolygon();
    void classify();
    void addPoint();
    void clear();
    void readPolygon();
};