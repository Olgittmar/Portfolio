#include "PointInPolygon.h"

// Own
#include <Polygon.h>

namespace Solutions {

std::string
PointInPolygon( std::istream& in, std::ostream& out)
{
    using namespace std;
    string line, ret;
    int numVertices, numPoints;
    bool readyToClassify = false;
    utils::Polygon poly;
    utils::Point testPoint;

    while ( getline( in, line ) ){
        if( readyToClassify ) {
            if( ( numPoints = atoi( line.c_str() ) ) ) {
                for( int i = 0; i < numPoints; i++) {
                    getline( in, line );
                    testPoint = utils::Point( line );
                    ret += poly.classify( testPoint ) + '\n';
                }
            }
            readyToClassify = false;
        } else {
            numVertices = atoi( line.c_str() );
            if ( numVertices != 0 ){
                utils::Polygon::readPolygon( in, numVertices, poly );
                readyToClassify = true;
            }
        }
    }
    out << ret;
    return ret;
}

}