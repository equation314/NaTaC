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
    QPointF Position() const { return pos; }
    double Angle() const { return angle; }

    //QPointF StartPoint() const { return m_start->Point(); }
    //QPointF EndPoint() const { return m_end->Point(); }

    QRect Rect(double size);

protected:
    bool Contains(const QPointF& point, double length) const override;

    // Setter member functions

private:
    City *m_start, *m_end;
    QPointF pos;
    double angle;
};

#endif // ROAD_H
