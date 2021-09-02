#include "PointInPolygon.h"

// Own
#include <Polygon.h>

namespace Solutions {

std::string
PointInPolygon( std::istringstream& in, std::ostringstream& out)
{
    std::string line, _ret;
    utils::Polygon poly;
    utils::Point testPoint;

    while ( std::getline(in, line, '\n') ) {
        int numVertices = std::stoi( line );
        if ( numVertices == 0 ){
            break;
        }

        poly.clear();
        utils::Polygon::readPolygon( in, numVertices, poly );

        std::getline( in, line, '\n' );
        int numPoints = std::stoi( line );
        
        if( !_ret.empty() ){
            _ret += '\n';
        }

        for( int i = 0; i < numPoints; ++i ) {
            std::getline( in, line, '\n' );
            testPoint = utils::Point( line );
            if( i > 0 ){
                _ret += '\n';
            }
            _ret += poly.classify( testPoint );
        }
    }
    out << _ret;
    return _ret;
}

}