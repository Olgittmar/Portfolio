#pragma once
// Std
#include <string>
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
        ExtraWhitespace, Generic, GenericAutogenAnswers,
        RandGen, RandGenST, RandGenBM
    };
    Q_ENUM(MYTESTS);
    
  private:
    static const char delim = '\n';
    static const char subdelim = ' ';

    QPolygon pointsToQPolygon( const std::vector<utils::Point>& v ) const;
    // Attempts to generate testData for PointInPolygon. Max values are arbitrarily chosen for now.
    QString generatePIPTestData(
        bool stressTest = false, int maxNumPolygons = 11,
        int maxNumVertices = 10000, int maxNumTestPoints = 10000 );
    QString generatePIPAnswers( const QString& testData ) const;
    std::string strDiff( const std::string& str1, const std::string& str2 ) const;

  private slots:
    void initTestCase_data();

    void PointInPolygon();
};