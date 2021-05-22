// std
#include <iostream>
#include <fstream>

// Own
#include "PointInPolygon.h"

using namespace std;

int
main( int argc, char* argv[] )
{
    cout << "Running main!" << endl;
    ifstream f;
    string filepath = "data/point_in_polygon.in";
    string result;
    f.open( filepath );
    if( f.is_open() ){
        result = PointInPolygon::PointInPolygon( f, cout );
    } else {
        cout << "Unable to open " << "data/point_in_polygon.in" << endl;
    }
    cin.ignore();
    return 0;
}
