#include "const.h"
#include "mapwidget.h"

#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

using namespace std;

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{
    for (int i = 0; i < 19; i++)
        m_tile[i] = new Tile;

    buildTile();
}

MapWidget::~MapWidget()
{
    for (int i = 0; i < 19; i++)
        delete m_tile[i];
}

void MapWidget::resizeEvent(QResizeEvent* event)
{
    //qDebug()<<' '<<this->visibleRegion();
    buildTile();
    QWidget::resizeEvent(event);
}

void MapWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    qDebug()<<this->rect();
    painter.setBrush(QColor(0, 132, 255));
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
    for (int i = 0; i < 19; i++)
    {
        painter.setBrush(m_tile[i]->Color());
        //qDebug()<<tile.ToPolygon();
        painter.drawPolygon(m_tile[i]->ToPolygon());
    }
    QWidget::paintEvent(event);
}

void MapWidget::buildTile()
{
    m_center = QPointF(this->width() / 2, this->height() / 2);
    m_size = min(this->height() / 8.0, this->width() / 5 / Const::SQRT3) * 0.85;

    m_tile[0]->SetGeometry(m_center + QPointF(-1 * Const::SQRT3 * m_size, -3 * m_size), m_size);
    m_tile[1]->SetGeometry(m_center + QPointF( 0 * Const::SQRT3 * m_size, -3 * m_size), m_size);
    m_tile[2]->SetGeometry(m_center + QPointF( 1 * Const::SQRT3 * m_size, -3 * m_size), m_size);

    m_tile[3]->SetGeometry(m_center + QPointF(-1.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tile[4]->SetGeometry(m_center + QPointF(-0.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tile[5]->SetGeometry(m_center + QPointF( 0.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tile[6]->SetGeometry(m_center + QPointF( 1.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);

    m_tile[7]->SetGeometry( m_center + QPointF(-2 * Const::SQRT3 * m_size, 0), m_size);
    m_tile[8]->SetGeometry( m_center + QPointF(-1 * Const::SQRT3 * m_size, 0), m_size);
    m_tile[9]->SetGeometry( m_center + QPointF( 0 * Const::SQRT3 * m_size, 0), m_size);
    m_tile[10]->SetGeometry(m_center + QPointF( 1 * Const::SQRT3 * m_size, 0), m_size);
    m_tile[11]->SetGeometry(m_center + QPointF( 2 * Const::SQRT3 * m_size, 0), m_size);

    m_tile[12]->SetGeometry(m_center + QPointF(-1.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tile[13]->SetGeometry(m_center + QPointF(-0.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tile[14]->SetGeometry(m_center + QPointF( 0.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tile[15]->SetGeometry(m_center + QPointF( 1.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);

    m_tile[16]->SetGeometry(m_center + QPointF(-1 * Const::SQRT3 * m_size, 3 * m_size), m_size);
    m_tile[17]->SetGeometry(m_center + QPointF( 0 * Const::SQRT3 * m_size, 3 * m_size), m_size);
    m_tile[18]->SetGeometry(m_center + QPointF( 1 * Const::SQRT3 * m_size, 3 * m_size), m_size);
}
