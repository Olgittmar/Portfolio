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
    const QString testdir{"testPointInPolygonData"};
  private slots:
    void initTestCase_data();
    // void initTestCase();
};