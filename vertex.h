#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>
#include <QColor>

class Tile;
class Vertex
{
public:
    Vertex();

    void Move(const QPointF& center) { m_center = center; }

private:
    const int m_range = 10;

    QPointF m_center;
    QColor m_color;
    int m_neighbor_count;
    Tile* m_neighbor[3];
};

#endif // VERTEX_H
