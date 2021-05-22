#pragma once

// Std
#include <string>
#include <iostream>

// Own
#include <Coordinates/Polygon.h>

using namespace std;

namespace PointInPolygon {

string
PointInPolygon( istream& in, ostream& out);

void
readPolygon( istream& in, const int numLines, utils::Polygon& out );

}