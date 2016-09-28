#ifndef TILE_H
#define TILE_H

#include "building.h"

#include <QColor>
#include <QPolygonF>

class Tile
{
public:
    enum RobberState { NoneState, HoverState, PlacedState };

    Tile(Const::Resource type, int num);

    // Getter member functions
    int Number() const { return m_number; }
    Const::Resource Type() const { return m_type; }
    QColor Color() const { return Const::RESOURCE_COLOR[m_type]; }
    QPointF Center() const { return m_center;}
    QPolygonF Polygon() const { return m_polygon; }
    City* CityAt(int p) const { return m_cities[p]; }
    RobberState GetRobberState() const { return m_robber_state; }

    // Setter member functions
    void SetCity(int p, City* city) { m_cities[p] = city; }
    void SetGeometry(const QPointF& center, double size);
    void SetRobberState(RobberState state) { m_robber_state = state; }

private:
    QPointF m_center;
    QPolygonF m_polygon;
    Const::Resource m_type;
    int m_number;
    double m_size; /// Side length of the hexagonal tile
    City* m_cities[6];

    RobberState m_robber_state;

    void buildPolygon();
};

#endif // TILE_H
