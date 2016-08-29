#include "road.h"

Road::Road(City* start, City* end) :
    m_start(start), m_end(end), pos(m_start->Point())
{
    QPointF p = m_end->Point() - m_start->Point();
    angle = atan2(p.y(), p.x());
}

QRect Road::Rect(double size)
{

}

bool Road::Contains(const QPointF &point, double length) const
{

}
