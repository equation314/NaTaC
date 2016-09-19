#ifndef TILE_H
#define TILE_H

#include "building.h"

#include <QColor>
#include <QPolygonF>

class Tile
{
public:
    Tile(int number);
    //Tile(double x, double y, double size);
    //Tile(const QPointF& center, double size);

    // Getter member functions
    int Number() const { return m_number; }
    QColor Color() const { return m_color; }
    QPointF Center() const { return m_center;}
    QPolygonF Polygon() const { return m_polygon; }

    // Setter member functions
    void SetCity(int p, City* city) { m_cities[p] = city; }
    void SetGeometry(const QPointF& center, double size);
    void SetColor(const QColor& color) { m_color = color; }

private:
    QPointF m_center;
    QPolygonF m_polygon;
    QColor m_color;
    int m_number;
    double m_size; /// Side length of the hexagonal tile
    City* m_cities[6];

    void buildPolygon();
};

#endif // TILE_H
