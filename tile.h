#ifndef TILE_H
#define TILE_H

#include "city.h";

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
    QPolygonF Polygon() const { return m_polygon; }

    // Setter member functions
    void SetCity(int p, City* city) { m_cities[p] = city; }
    void SetGeometry(const QPointF& center, double size);
    void SetColor(const QColor& color) { m_color = color; }

private:
    QPointF m_center;
    QPolygonF m_polygon;
    QColor m_color;
    double m_size;
    City* m_cities[6];

    void buildPolygon();
};

#endif // TILE_H
