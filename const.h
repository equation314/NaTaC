#ifndef CONST_H
#define CONST_H

#include <cmath>

namespace Const
{
const int TILE_COUNT = 19;
const int CITY_COUNT = 54;
const int ROAD_COUNT = 72;
const double SQRT3 = sqrt(3);
const double EPS = 1e-6;
const double PI = acos(-1);

inline double Sqr(double x) { return x * x; }

}

#endif // CONST_H
