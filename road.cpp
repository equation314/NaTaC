#include "road.h"

#include <QDebug>

Road::Road(City* start, City* end) :
    m_start(start), m_end(end)
{
    QPointF p = m_end->Point() - m_start->Point();
    m_angle = atan2(p.y(), p.x());
}

bool Road::CanPlace() const
{
    if (this->IsBuilt()) return false;
    if (m_start->Owner() == Player::CurrentPlayer() || m_end->Owner() == Player::CurrentPlayer())
        return true;
    for (int i = 0; i < m_start->RoadCount(); i++)
        if (m_start->RoadAt(i)->Owner() == Player::CurrentPlayer())
            return true;
    for (int i = 0; i < m_end->RoadCount(); i++)
        if (m_end->RoadAt(i)->Owner() == Player::CurrentPlayer())
            return true;
    return false;
}

bool Road::Contains(const QPointF &point, double length) const
{
    QPointF o = m_start->Point();
    double x, y;
    x = (point.x() - o.x()) * cos(-m_angle) - (point.y() - o.y()) * sin(-m_angle) + o.x();
    y = (point.x() - o.x()) * sin(-m_angle) + (point.y() - o.y()) * cos(-m_angle) + o.y();
    QRectF rect(o.x(), o.y() - length / 4, 3 * length / 4, length / 2);

    return rect.contains(x, y);
}
