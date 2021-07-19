#include "utils.h"

namespace utils {

int
randInt( int min, int max ) {
    static std::uniform_int_distribution<int> distr{min, max};
    static std::random_device engine;
    static std::mt19937 noise{engine()};
    return distr(noise);
};

}