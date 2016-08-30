#ifndef ROAD_H
#define ROAD_H

#include "city.h"

#include <QRect>

class Road : public Building
{
public:
    Road();
    Road(City* start, City* end);

    // Getter member function
    double AngleR() const { return m_angle; }
    double AngleD() const { return m_angle * 180 / Const::PI; }

    City* Start() const { return m_start; }
    City* End() const { return m_end; }

    QPointF StartPoint() const { return m_start->Point(); }
    QPointF EndPoint() const { return m_end->Point(); }

    // Setter member functions

    bool CanPlace() const override;
    BuildingType Type() const override { return RoadType; }
    BuildingState MaxLevel() const override { return Level1; }
    bool Contains(const QPointF& point, double length) const override;


private:
    City *m_start, *m_end;
    double m_angle;
};

#endif // ROAD_H
