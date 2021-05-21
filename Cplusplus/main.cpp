// std
#include <iostream>

// Own
#include "PointInPolygon.h"

using namespace std;

class Test {
  public:
    Test() = default;
    ~Test() = default;

    inline void cry() const { printf("I am Test!"); };
};

int
main( int argc, char* argv[] )
{
    printf( "Hello World!" );
    cin.ignore();
    return 0;
}
