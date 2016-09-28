#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include "tile.h"
#include "const.h"

#include <QWidget>

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget* parent = nullptr);
    ~MapWidget();

    void SetCanMoveRobber(bool can) { if (can) m_robber_state = RobberPlaced; else m_robber_state = CannotMoveRobber; }
    void SetCurrentBuilding(Building::BuildingType type) { m_current_building = type; }
    void Load(Const::Resource type[Const::TILE_COUNT], int num[Const::TILE_COUNT]);
    void ObtainResources(int number);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    enum RobberState { CannotMoveRobber, RobberMoving, RobberPlaced };

    Tile* m_tiles[Const::TILE_COUNT];
    City* m_cities[Const::CITY_COUNT];
    Road* m_roads[Const::ROAD_COUNT];
    double m_size; /// Side length of the hexagonal tile
    QPointF m_center;
    Building::BuildingType m_current_building;
    bool m_loaded;

    RobberState m_robber_state;
    Tile* m_robber_tile;

    QRectF robberRect(const QPointF& center);
    void drawRobber(QPainter *painter, const QPointF &center, bool isTransparent = false);
    void buildTiles();

signals:
    void obtainedResources(int cnt[Const::RESOURCE_COUNT]);
    void robberPlaced(Tile* tile);
    void buildingBuilt(Building* building);
};

#endif // MAPWIDGET_H
