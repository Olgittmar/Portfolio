#include "PointInPolygon.h"

// Own
#include <Polygon.h>

namespace Solutions {

std::string
PointInPolygon( std::istringstream& in, std::ostringstream& out)
{
    std::string line;
    utils::Polygon poly;
    utils::Point testPoint;

    while ( std::getline(in, line, '\n') ) {
        int numVertices = std::stoi( line );
        if ( numVertices == 0 ){
            break;
        }
        poly.clear();
        utils::Polygon::readPolygon( in, numVertices, poly );
        if( !out.str().empty() ){
            out << '\n';
        }

        std::getline( in, line, '\n' );
        int numPoints = std::stoi( line );
        for( int i = 0; i < numPoints; i++) {
            std::getline( in, line, '\n' );
            if( i > 0 ){
                out << '\n';
            }
            testPoint = utils::Point( line );
            out << poly.classify( testPoint );
        }
    }
    return out.str();
}

}