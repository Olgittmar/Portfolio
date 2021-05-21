#include "PointInPolygon.h"

string
PointInPolygon( istream& in, ostream& out)
{
    string line, ret;
    int numVertices, numPoints;
    bool readyToClassify = true;
    utils::Polygon poly;
    utils::Point testPoint;

    while ( getline( in, line ) ){
        if( readyToClassify ) {
            if( numPoints = atoi( line.c_str() ) ) {
                for( int i = 0; i < numPoints; i++) {
                    getline( in, line );
                    testPoint = utils::Point( line );
                    ret += poly.classify( testPoint ) + '\n';
                }
            }
        } else {
            numVertices = atoi( line.c_str() );
            if ( numVertices != 0 ){
                readPolygon( in, numVertices, poly );
                readyToClassify = true;
            }
        }
    }
    return ret;
}

//TODO this could be improved by reading the entire block, and then subdividing into Points from which the polygon is created.
void
readPolygon( istream& in, const int numLines, utils::Polygon& out ) {
    string line;
    utils::Point p;
    for( int i = 0; i < numLines; i++ ){
        getline( in, line );
        p = utils::Point( line );
        out.addPoint( p );
    }
}