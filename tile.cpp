#include "city.h"
#include "tile.h"

#include <QDebug>

Tile::Tile()
{
    for (int i = 0; i < 6; i++)
        m_cities[i] = nullptr;
}
/*
Tile::Tile(double x, double y, double size) :
    m_center(x, y), m_size(size)
{
    buildPolygon();
}

Tile::Tile(const QPointF& center, double size) :
    m_center(center), m_size(size)
{
    buildPolygon();
}*/

void Tile::SetGeometry(const QPointF &center, double size)
{
    m_size = size;
    m_center = center;
    buildPolygon();
}

void Tile::buildPolygon()
{
    m_color = Qt::red;
    m_polygon.clear();
    m_polygon << m_center + QPointF(0, -m_size)
              << m_center + QPointF(-m_size * Const::SQRT3/ 2, -m_size / 2)
              << m_center + QPointF(-m_size * Const::SQRT3/ 2,  m_size / 2)
              << m_center + QPointF(0,  m_size)
              << m_center + QPointF( m_size * Const::SQRT3/ 2,  m_size / 2)
              << m_center + QPointF( m_size * Const::SQRT3/ 2, -m_size / 2);
    for (int i = 0; i < 6; i++)
        if (m_cities[i] != nullptr) m_cities[i]->SetPoint(m_polygon[i]);

    //qDebug()<<center<<' '<<m_size<<' '<<' '<<m_polygon;
}
