#ifndef TILE_H
#define TILE_H

#include "vertex.h";

#include <QColor>
#include <QPolygonF>

class Tile
{
public:
    Tile();
    //Tile(double x, double y, double size);
    //Tile(const QPointF& center, double size);

    // Getter member functions
    QColor Color() const { return m_color; }
    QPolygonF ToPolygon() const { return m_polygon; }
    QPointF& operator [](int x) { return m_polygon[x]; }
    const QPointF& operator [](int x) const { return m_polygon[x]; }

    // Setter member functions
    void SetGeometry(const QPointF& center, double size);
    void SetColor(const QColor& color) { m_color = color; }

private:
    QPointF m_center;
    QPolygonF m_polygon;
    QColor m_color;
    double m_size;
    Vertex* vertex[6];

    void buildPolygon();
};

#endif // TILE_H
