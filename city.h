#ifndef CITY_H
#define CITY_H

#include "building.h"

class City : public Building
{
public:
    City(const QPointF& point);

    // Getter member functions
    QPointF Point() const { return m_point; }
    int RoadCount() const { return m_road_count; }
    Road* RoadAt(int i) const { return m_roads[i]; }
    double Distance2(const QPointF& point) const
    {
        return Const::Sqr(m_point.x() - point.x()) + Const::Sqr(m_point.y() - point.y());
    }
    double Distance2(City* city) const { return Distance2(city->Point()); }

    // Setter member functions
    void SetPoint(const QPointF& point) { m_point = point; }
    void AddRoad(Road* road) { m_roads[m_road_count++] = road; }

    bool CanPlace()  const override;
    BuildingClass Class() const override { return CityClass; }
    bool Contains(const QPointF& point, double radius) const override
    {
        return Distance2(point) <= Const::Sqr(radius);
    }

private:
    QPointF m_point;
    int m_road_count;
    Road* m_roads[3];
};

#endif // CITY_H
