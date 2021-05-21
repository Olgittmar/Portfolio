#pragma once

// Std
#include <string>
#include <iostream>

// Own
#include "Polygon.h"

using namespace std;

string
PointInPolygon( istream& in, ostream& out);

void
readPolygon( istream& in, const int numLines, utils::Polygon& out );