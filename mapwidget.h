#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include "tile.h"
#include "const.h"

#include <QWidget>

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();

    void SetCurrentBuilding(Building::BuildingType type) { m_current_building = type; }

public slots:

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Tile* m_tiles[Const::TILE_COUNT];
    City* m_cities[Const::CITY_COUNT];
    Road* m_roads[Const::ROAD_COUNT];
    double m_size; /// Side length of the hexagonal tile
    QPointF m_center;
    Building::BuildingType m_current_building;

    void buildTiles();

signals:
    void buildingBuilt(Building* building, int id);
};

#endif // MAPWIDGET_H
