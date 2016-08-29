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

    QPointF StartPoint() const { return m_start->Point(); }
    QPointF EndPoint() const { return m_end->Point(); }

    bool Contains(const QPointF& point, double length) const override;

    // Setter member functions

private:
    City *m_start, *m_end;
    double m_angle;
};

#endif // ROAD_H
