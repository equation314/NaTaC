#ifndef CONST_H
#define CONST_H

#include <cmath>
#include <QColor>
#include <QObject>

namespace Const
{

enum Resource
{
    Brick,
    Lumber,
    Wool,
    Grain,
    Ore,
    Desert,
};

enum DevelopmentCardType
{
    SoldierCard,
    PointCard,
    RoadsCard,
    MonopolyCard,
    HarvestCard,
};

const double SQRT3 = sqrt(3);
const double EPS = 1e-6;
const double PI = acos(-1);

const int TILE_COUNT = 19;
const int CITY_COUNT = 54;
const int ROAD_COUNT = 72;
const int RESOURCE_COUNT = 5;
const int INITIAL_ROAD_COUNT = 2;
const int INITIAL_CITY_COUNT = 2;

const int COST[4][RESOURCE_COUNT] =
{
    {1, 1, 0, 0, 0},
    {1, 1, 1, 1, 0},
    {0, 0, 0, 2, 3},
    {0, 0, 1, 1, 1},
};

inline double Sqr(double x) { return x * x; }

const QColor PLAYER_COLOR[] =
{
    Qt::blue,
    Qt::green,
    Qt::red,
    Qt::yellow,
    Qt::white,
    Qt::gray,
};

const QColor RESOURCE_COLOR[] =
{
    QColor(180, 56, 1),
    QColor(0, 168, 0),
    QColor(131, 255, 29),
    QColor(255, 170, 0),
    QColor(108, 108, 108),
    QColor(255, 217, 85),
};

const QString RESOURCE_NAME[] =
{
    QObject::tr("brick"),
    QObject::tr("lumber"),
    QObject::tr("wool"),
    QObject::tr("grain"),
    QObject::tr("ore"),
    QObject::tr("desert"),
};

const QString DEV_CARD_NAME[] =
{
    QObject::tr("Soldier Card"),
    QObject::tr("1 victory point"),
    QObject::tr("Roads Card"),
    QObject::tr("Monopoly Card"),
    QObject::tr("Harvest Card"),
};

}

#endif // CONST_H
