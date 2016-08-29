#include "const.h"
#include "mapwidget.h"

#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

using namespace std;

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);

    for (int i = 0; i < Const::CITY_COUNT; i++)
        m_cities[i] = nullptr;
    for (int i = 0; i < Const::TILE_COUNT; i++)
        m_tiles[i] = new Tile;

    buildTiles();
    for (int i = 0, t = 0; i < Const::TILE_COUNT; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            City* city = nullptr;
            for (int k = 0; k < t; k++)
                if (m_cities[k]->Distance2(m_tiles[i]->Polygon()[j]) < Const::EPS) city = m_cities[k];
            //qDebug()<<i<<' '<<j<<' '<<city<<' '<<n<<' '<<m_tiles[i]->Polygon()[j];
            if (city == nullptr)
            {
                city = new City(m_tiles[i]->Polygon()[j]);
                m_cities[t++] = city;
            }
            m_tiles[i]->SetCity(j, city);
        }
    }

    for (int i = 0, t = 0; i < Const::CITY_COUNT; i++)
        for (int j = i + 1; j < Const::CITY_COUNT; j++)
            if (m_cities[i]->Distance2(m_cities[j]->Point()) - Const::Sqr(m_size) < Const::EPS)
            {
                m_roads[t++] = new Road(m_cities[i], m_cities[j]);
            }

    for (int i = 0; i < Const::CITY_COUNT; i++)
        m_cities[i]->SetColor(Qt::green);

    for (int i = 0; i < Const::ROAD_COUNT; i++)
        m_roads[i]->SetColor(Qt::green);
}

MapWidget::~MapWidget()
{
    for (int i = 0; i < Const::TILE_COUNT; i++)
        delete m_tiles[i];

    for (int i = 0; i < Const::TILE_COUNT; i++)
        delete m_cities[i];

    for (int i = 0; i < Const::TILE_COUNT; i++)
        delete m_roads[i];
}

void MapWidget::resizeEvent(QResizeEvent* event)
{
    //qDebug()<<' '<<this->visibleRegion();
    buildTiles();
    QWidget::resizeEvent(event);
}

void MapWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBrush(QColor(0, 132, 255));
    painter.drawRect(0, 0, this->width() - 1, this->height() - 1);
    for (int i = 0; i < Const::TILE_COUNT; i++)
    {
        painter.setBrush(m_tiles[i]->Color());
        painter.drawPolygon(m_tiles[i]->Polygon());
    }

    for (int i = 0; i < Const::ROAD_COUNT; i++)
        if (m_roads[i]->State() != Building::None)
        {
            switch (m_roads[i]->State())
            {
            case Building::Hover:
                painter.setBrush(m_cities[i]->TransparentColor());
                break;
            case Building::Level1:
                painter.setBrush(m_cities[i]->Color());
                break;
            }
            painter.save();
            painter.translate(m_roads[i]->StartPoint());
            painter.rotate(m_roads[i]->AngleD());
            painter.drawRect(m_size / 8, -m_size / 12, 3 * m_size / 4, m_size / 6);
            painter.restore();
        }

    for (int i = 0; i < Const::CITY_COUNT; i++)
        switch (m_cities[i]->State())
        {
        case Building::Hover:
            painter.setBrush(m_cities[i]->TransparentColor());
            painter.drawEllipse(m_cities[i]->Point(), m_size / 5, m_size / 5);
            break;
        case Building::Level1:
            painter.setBrush(m_cities[i]->Color());
            painter.drawEllipse(m_cities[i]->Point(), m_size / 5, m_size / 5);
            break;
        case Building::Level2:
            painter.setBrush(m_cities[i]->Color());
            painter.drawRect(m_cities[i]->Point().x() - m_size / 5, m_cities[i]->Point().y() - m_size / 5, m_size / 2.5, m_size / 2.5);
            break;
        }

    QWidget::paintEvent(event);
}

void MapWidget::mouseMoveEvent(QMouseEvent* event)
{
    bool hovered = false;

    for (int i = 0; i < Const::CITY_COUNT; i++)
        if (m_cities[i]->State() != Building::Level1 && m_cities[i]->State() != Building::Level2)
        {
            if (m_cities[i]->Contains(event->pos(), m_size / 5) && !hovered)
            {
                m_cities[i]->SetState(Building::Hover);
                hovered = true;
            }
            else
                m_cities[i]->SetState(Building::None);
        }

    for (int i = 0; i < Const::ROAD_COUNT; i++)
        if (m_roads[i]->State() != Building::Level1)
        {
            if (m_roads[i]->Contains(event->pos(), m_size) && !hovered)
            {
                m_roads[i]->SetState(Building::Hover);
                hovered = true;
            }
            else
                m_roads[i]->SetState(Building::None);
        }
    this->update();
    QWidget::mouseMoveEvent(event);
}

void MapWidget::mousePressEvent(QMouseEvent* event)
{
    for (int i = 0; i < Const::ROAD_COUNT; i++)
        if (m_roads[i]->Contains(event->pos(), m_size) && m_roads[i]->State() == Building::Hover)
            m_roads[i]->SetState(Building::Level1);

    for (int i = 0; i < Const::CITY_COUNT; i++)
        if (m_cities[i]->Contains(event->pos(), m_size / 5))
        {
            if (m_cities[i]->State() == Building::Hover)
                m_cities[i]->SetState(Building::Level1);
            else if (m_cities[i]->State() == Building::Level1)
                m_cities[i]->SetState(Building::Level2);
        }
    this->update();
    QWidget::mouseMoveEvent(event);
}


void MapWidget::buildTiles()
{
    m_center = QPointF(this->width() / 2, this->height() / 2);
    m_size = min(this->height() / 8.0, this->width() / 5 / Const::SQRT3) * 0.85;

    m_tiles[0]->SetGeometry(m_center + QPointF(-1 * Const::SQRT3 * m_size, -3 * m_size), m_size);
    m_tiles[1]->SetGeometry(m_center + QPointF( 0 * Const::SQRT3 * m_size, -3 * m_size), m_size);
    m_tiles[2]->SetGeometry(m_center + QPointF( 1 * Const::SQRT3 * m_size, -3 * m_size), m_size);

    m_tiles[3]->SetGeometry(m_center + QPointF(-1.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tiles[4]->SetGeometry(m_center + QPointF(-0.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tiles[5]->SetGeometry(m_center + QPointF( 0.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tiles[6]->SetGeometry(m_center + QPointF( 1.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);

    m_tiles[7]->SetGeometry( m_center + QPointF(-2 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[8]->SetGeometry( m_center + QPointF(-1 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[9]->SetGeometry( m_center + QPointF( 0 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[10]->SetGeometry(m_center + QPointF( 1 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[11]->SetGeometry(m_center + QPointF( 2 * Const::SQRT3 * m_size, 0), m_size);

    m_tiles[12]->SetGeometry(m_center + QPointF(-1.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tiles[13]->SetGeometry(m_center + QPointF(-0.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tiles[14]->SetGeometry(m_center + QPointF( 0.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tiles[15]->SetGeometry(m_center + QPointF( 1.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);

    m_tiles[16]->SetGeometry(m_center + QPointF(-1 * Const::SQRT3 * m_size, 3 * m_size), m_size);
    m_tiles[17]->SetGeometry(m_center + QPointF( 0 * Const::SQRT3 * m_size, 3 * m_size), m_size);
    m_tiles[18]->SetGeometry(m_center + QPointF( 1 * Const::SQRT3 * m_size, 3 * m_size), m_size);

    /*for (int i = 0; i < Const::CITY_COUNT; i++)
        if (m_cities[i]) qDebug()<<i<<' '<<m_cities[i]->Point()<<' '<<m_cities[i]->State();*/
}
