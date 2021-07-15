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
  public:
    enum MYTESTS {
        Empty, Invalid,
        Unreasonably_large_Coordinates,
        Q1_Triangle, Q2_Triangle,
        Q3_Triangle, Q4_Triangle,
        Upright_Square, Diamond, Star
    };
    Q_ENUM(MYTESTS)

  private slots:
    void initTestCase_data();
    void classify_data();
    void iteratePolygon_data();
    void operatorOstrm_data();

    void initPolygon();
    void iteratePolygon();
    void operatorEquals();
    void classify();
    void addPoint();
    void clear();
    void readPolygon();
    void operatorOstrm();
};