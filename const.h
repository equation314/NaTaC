#ifndef CONST_H
#define CONST_H

#include <cmath>
#include <QColor>
#include <QList>

namespace Const
{
const double SQRT3 = sqrt(3);
const double EPS = 1e-6;
const double PI = acos(-1);

const int TILE_COUNT = 19;
const int CITY_COUNT = 54;
const int ROAD_COUNT = 72;
const int INITIAL_CITY_COUNT = 1;

inline double Sqr(double x) { return x * x; }

const QList<QColor> PLAYER_COLOR =
{
    Qt::green,
    Qt::blue,
    Qt::red,
    Qt::yellow,
    Qt::white,
    Qt::gray,
};

}

#endif // CONST_H
