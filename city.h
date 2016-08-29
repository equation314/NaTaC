#ifndef CITY_H
#define CITY_H

#include "const.h"
#include "building.h"

class Tile;
class City : public Building
{
public:
    City();
    City(const QPointF& point);

    // Getter member functions
    QPointF Point() const { return m_point; }
    double Distance2(const QPointF& point) const
    {
        return Const::Sqr(m_point.x() - point.x()) + Const::Sqr(m_point.y() - point.y());
    }
    double Distance2(City* city) const { return Distance2(city->Point()); }

    // Setter member functions
    void SetPoint(const QPointF& point) { m_point = point; }

    bool Contains(const QPointF& point, double radius) const override
    {
        return Distance2(point) <= Const::Sqr(radius);
    }

private:
    QPointF m_point;
    int m_neighbor_count;
    Tile* m_neighbor[3];
};

#endif // CITY_H
