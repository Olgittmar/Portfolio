#pragma once
// Qt
#include <QTest>
#include <QPolygon>
// Own
#include <utils.h>
#include <Point.h>
#include <PointInPolygon.h>

class TestPointInPolygon: public QObject
{
  Q_OBJECT
  public:
    enum MYTESTS {
        Empty, InvalidFormat,
        ExtraWhitespace, Generic,
        RandGen, RandGenST, RandGenBM
    };
    Q_ENUM(MYTESTS);
    
  private:
    // perhaps move to init or resource file, but hardcoded is ok for now.
    static const QString testdir{"testPointInPolygonData"};
    static const int maxNumPolygons = 11;
    static const int reasonableNumPoints = 63;
    static const int maxNumVertices = 10000;
    static const int maxNumTestPoints = 1000;
    static const int numSSVertices = 1000000;
    static const int numBMVertices = maxNumVertices;
    static const char delim = '\n';
    static const char subdelim = ' ';

    QPolygon pointsToQPolygon( const std::vector<utils::Point>& v ) const;
    // Generates a random point with x, y in [INT_MIN, INT_MAX]
    utils::Point randPoint() const { return utils::Point( utils::randInt(), utils::randInt() ); }

  private slots:
    void initTestCase_data();
    void initTestCase();

    void PointInPolygon();
};