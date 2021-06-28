#pragma once
// Qt
#include <QTest>
// Own
#include <Line.h>


// --------------------------------------------------------------------------
// TEST CLASS
// --------------------------------------------------------------------------
class TestLine: public QObject
{
  Q_OBJECT
  private slots:
    void initTestCase_data();
    void internalPointsInitialized();

    void aboveLine();
    void belowLine();
    void leftOfLine();
    void rightOfLine();
    
    void aboveMidpoint();
    void belowMidpoint();
    void leftOfMidpoint();
    void rightOfMidpoint();

    void slope();
    void invSlope();
    void slopeQuadrant();
    void isAngled();

    void inHRange_data();
    void inVRange_data();
    void inHRange();
    void inVRange();
    void yAt();
    void xAt();
    void intersects_data();
    void includes_data();
    void intersects();
    void includes();
};
