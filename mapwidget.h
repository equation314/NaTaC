#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include "road.h"
#include "tile.h"
#include "const.h"
#include "city.h"

#include <QWidget>

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Tile* m_tiles[Const::TILE_COUNT];
    City* m_cities[Const::CITY_COUNT];
    Road* m_roads[Const::ROAD_COUNT];
    double m_size;
    QPointF m_center;

    void buildTiles();
};

#endif // MAPWIDGET_H
