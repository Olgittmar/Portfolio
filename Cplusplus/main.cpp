// std
#include <iostream>
#include <fstream>

// Own
#include "src/solutions/PointInPolygon.h"

int
main( int argc, char* argv[] )
{
    using namespace std;
    cout << "Running main!" << endl;
    ifstream f;
    string filepath = "data/point_in_polygon.in";
    string result;
    f.open( filepath );
    if( f.is_open() ){
        result = Solutions::PointInPolygon( f, cout );
    } else {
        cout << "Unable to open " << "data/point_in_polygon.in" << endl;
    }
    cin.ignore();
    return 0;
}
