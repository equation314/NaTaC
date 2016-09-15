#ifndef CONST_H
#define CONST_H

#include <cmath>
#include <QColor>
#include <QList>

namespace Const
{

enum Resource
{
    Brick,
    Lumber,
    Wool,
    Grain,
    Ore
};

const double SQRT3 = sqrt(3);
const double EPS = 1e-6;
const double PI = acos(-1);

const int TILE_COUNT = 19;
const int CITY_COUNT = 54;
const int ROAD_COUNT = 72;
const int RESOURCES_COUNT = 5;
const int INITIAL_ROAD_COUNT = 2;
const int INITIAL_CITY_COUNT = 2;

const int DEPEND[4][RESOURCES_COUNT] =
{
    {1, 1, 0, 0, 0},
    {1, 1, 0, 1, 1},
    {0, 0, 0, 2, 3},
    {0, 0, 1, 1, 1}
};

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
