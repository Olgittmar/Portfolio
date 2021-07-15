#pragma once
// Qt
#include <QTest>
// Own
#include <PointInPolygon.h>

class TestPointInPolygon: public QObject
{
  Q_OBJECT
  public:
    enum MYTESTS {
        Empty, InvalidFormat,
        ExtraWhitespace, Generic,
        RandGen, RandGenSS, RandGenBM
    };
    Q_ENUM(MYTESTS);
    
  private:
    // perhaps move to init or resource file, but hardcoded is ok for now.
    const QString testdir{"testPointInPolygonData"};
    const int maxNumVertices = 1000;
    const int maxNumTestPoints = 1000;
    const int numSSVertices = 1000000;
    const int numBMVertices = maxNumVertices;

  private slots:
    void initTestCase_data();
    void initTestCase();
};