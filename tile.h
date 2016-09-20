#ifndef TILE_H
#define TILE_H

#include "building.h"

#include <QColor>
#include <QPolygonF>

class Tile
{
public:
    Tile(Const::Resource type, int num);
    //Tile(double x, double y, double size);
    //Tile(const QPointF& center, double size);

    // Getter member functions
    int Number() const { return m_number; }
    Const::Resource Type() const { return m_type; }
    QColor Color() const { return Const::RESOURCE_COLOR[m_type]; }
    QPointF Center() const { return m_center;}
    QPolygonF Polygon() const { return m_polygon; }
    City* CityAt(int p) const { return m_cities[p]; }

    // Setter member functions
    void SetCity(int p, City* city) { m_cities[p] = city; }
    void SetGeometry(const QPointF& center, double size);

private:
    QPointF m_center;
    QPolygonF m_polygon;
    Const::Resource m_type;
    int m_number;
    double m_size; /// Side length of the hexagonal tile
    City* m_cities[6];

    void buildPolygon();
};

#endif // TILE_H
