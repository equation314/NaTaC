#include "city.h"
#include "road.h"
#include "mapwidget.h"

#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

using namespace std;

MapWidget::MapWidget(QWidget* parent) :
    QWidget(parent),
    m_current_building(Building::NoneType), m_loaded(false),
    m_robber_state(CantMoveRobber), m_robber_tile(nullptr)
{
    this->setMouseTracking(true);

    memset(m_tiles, 0, sizeof(m_tiles));
    memset(m_cities, 0, sizeof(m_cities));
    memset(m_roads, 0, sizeof(m_roads));
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
    buildTiles();
    QWidget::resizeEvent(event);
}

void MapWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    painter.setBrush(QColor(0, 162, 232));
    painter.drawRect(0, 0, this->width() - 1, this->height() - 1);

    if (!m_loaded) return;

    // draw tiles
    for (int i = 0; i < Const::TILE_COUNT; i++)
    {
        painter.setBrush(m_tiles[i]->Color());
        painter.drawPolygon(m_tiles[i]->Polygon());

        int num = m_tiles[i]->Number();
        if (num)
        {
            painter.setBrush(Qt::white);
            painter.drawEllipse(m_tiles[i]->Center(), m_size / 3, m_size / 3);

            double len = m_size / 2;
            QFont font("Arial");
            font.setPixelSize(len / 4 * 3);
            painter.setFont(font);
            painter.setPen(QPen((num == 6 || num == 8) ? Qt::red : Qt::black));
            painter.drawText(QRectF(m_tiles[i]->Center().x() - len / 2, m_tiles[i]->Center().y() - len / 2, len, len), Qt::AlignCenter, QString::number(num));
            painter.setPen(Qt::black);
        }

        if (m_tiles[i]->GetRobberState() == Tile::PlacedState)
            drawRobber(&painter, m_tiles[i]->Center() - QPointF(0, m_size / 5));
        else if (m_tiles[i]->GetRobberState() == Tile::HoverState)
            drawRobber(&painter, m_tiles[i]->Center() - QPointF(0, m_size / 5), true);
    }

    // draw roads
    for (int i = 0; i < Const::ROAD_COUNT; i++)
        if (m_roads[i]->State() != Building::NoneState)
        {
            switch (m_roads[i]->State())
            {
            case Building::HoverState:
                painter.setBrush(m_cities[i]->TransparentColor());
                break;
            case Building::BuiltState:
                painter.setBrush(m_cities[i]->Color());
                break;
            default:
                break;
            }
            painter.save();
            painter.translate(m_roads[i]->StartPoint());
            painter.rotate(m_roads[i]->AngleD());
            painter.drawRect(m_size / 8, -m_size / 12, 3 * m_size / 4, m_size / 6);
            painter.restore();
        }

    // draw cities
    for (int i = 0; i < Const::CITY_COUNT; i++)
        if (m_cities[i]->State() != Building::NoneState)
        {
            if (m_cities[i]->State() == Building::HoverState)
                painter.setBrush(m_cities[i]->TransparentColor());
            else
                painter.setBrush(m_cities[i]->Color());

            if (m_cities[i]->Type() == Building::VillageType || (m_cities[i]->Type() == Building::NoneType && m_cities[i]->State() == Building::HoverState))
                painter.drawEllipse(m_cities[i]->Point(), m_size / 5, m_size / 5);
            if (m_cities[i]->Type() == Building::CityType || (m_cities[i]->Type() == Building::VillageType && m_cities[i]->State() == Building::HoverState))
                painter.drawRect(m_cities[i]->Point().x() - m_size / 5, m_cities[i]->Point().y() - m_size / 5, m_size / 2.5, m_size / 2.5);
        }

    // draw buildings with mouse
    if (m_current_building != Building::NoneType)
    {
        QPointF pos = this->mapFromGlobal(QCursor::pos());
        if (this->rect().contains(pos.x(), pos.y()))
        {
            painter.setBrush(Player::Self()->Color());
            switch (m_current_building)
            {
            case Building::RoadType:
                painter.drawRect(pos.x() - 3 * m_size / 8, pos.y() - m_size / 12, 3 * m_size / 4, m_size / 6);
                break;
            case Building::VillageType:
                painter.drawEllipse(pos, m_size / 5, m_size / 5);
                break;
            case Building::CityType:
                painter.drawRect(pos.x() - m_size / 5, pos.y() - m_size / 5, m_size / 2.5, m_size / 2.5);
                break;
            default:
                break;
            }
        }
    }

    if (m_robber_tile && m_robber_state == RobberMoving)
        drawRobber(&painter, this->mapFromGlobal(QCursor::pos()));

    QWidget::paintEvent(event);
}

void MapWidget::leaveEvent(QEvent* event)
{
    this->update();
    QWidget::leaveEvent(event);
}

void MapWidget::mouseMoveEvent(QMouseEvent* event)
{
    bool hovered = false;
    if (!m_loaded) return;

    // show translucent road
    for (int i = 0; i < Const::ROAD_COUNT; i++)
        if (!m_roads[i]->IsBuilt())
        {
            if (m_current_building == Building::RoadType && m_roads[i]->CanPlace() && m_roads[i]->Contains(event->pos(), m_size) && !hovered)
            {
                m_roads[i]->SetState(Building::HoverState);
                hovered = true;
            }
            else
                m_roads[i]->SetState(Building::NoneState);
        }

    // show translucent city
    for (int i = 0; i < Const::CITY_COUNT; i++)
    {
        if (((m_current_building == Building::VillageType && !m_cities[i]->IsBuilt()) ||
             (m_current_building == Building::CityType && m_cities[i]->Type() == Building::VillageType)) &&
            m_cities[i]->CanPlace() && m_cities[i]->Contains(event->pos(), m_size / 5) && !hovered)
        {
            m_cities[i]->SetState(Building::HoverState);
            hovered = true;
        }
        else if (m_cities[i]->State() == Building::HoverState)
        {
            if (!m_cities[i]->IsBuilt())
                m_cities[i]->SetState(Building::NoneState);
            else
                m_cities[i]->SetState(Building::BuiltState);
        }
    }

    // show translucent robber
    if (m_robber_state == RobberMoving)
    {
        for (int i = 0; i < Const::TILE_COUNT; i++)
        {
            if (m_tiles[i] != m_robber_tile && robberRect(m_tiles[i]->Center()).contains(event->pos()))
                m_tiles[i]->SetRobberState(Tile::HoverState);
            else
                m_tiles[i]->SetRobberState(Tile::NoneState);
        }
    }

    this->update();
    QWidget::mouseMoveEvent(event);
}

void MapWidget::mousePressEvent(QMouseEvent* event)
{
    if (!m_loaded) return;

    // place road
    if (m_current_building == Building::RoadType)
    {
        for (int i = 0; i < Const::ROAD_COUNT; i++)
            if (m_roads[i]->CanPlace() && m_roads[i]->Contains(event->pos(), m_size))
            {
                m_roads[i]->Build();
                emit buildingBuilt(m_roads[i]);
                break;
            }
    }

    // place city
    if (m_current_building == Building::VillageType || m_current_building == Building::CityType)
    {
        for (int i = 0; i < Const::CITY_COUNT; i++)
            if (m_cities[i]->CanPlace() && m_cities[i]->Contains(event->pos(), m_size / 5))
            {
                m_cities[i]->Build();
                emit buildingBuilt(m_cities[i]);
                if (m_cities[i]->Type() == Building::VillageType && Player::Self()->VillageCount() == Const::INITIAL_CITY_COUNT)
                {
                    int cnt[Const::RESOURCE_COUNT] = {0};
                    for (int j = 0; j < m_cities[i]->TiteCount(); j++)
                    {
                        Const::Resource res = m_cities[i]->TileAt(j)->Type();
                        if (res != Const::Desert)
                        {
                            Player::Self()->ObtainResources(res, 1);
                            cnt[(size_t)res]++;
                        }
                    }
                    emit obtainedResources(cnt);
                    break;
                }
            }
    }

    // place robber
    if (m_robber_state == RobberPlaced && robberRect(m_robber_tile->Center()).contains(event->pos()))
    {
        m_robber_state = RobberMoving;
        m_robber_tile->SetRobberState(Tile::NoneState);
        qDebug()<<233;
    }
    else if (m_robber_state == RobberMoving)
    {
        for (int i = 0; i < Const::TILE_COUNT; i++)
            if (m_tiles[i]->GetRobberState() == Tile::HoverState)
            {
                m_robber_tile = m_tiles[i];
                m_robber_tile->SetRobberState(Tile::PlacedState);
                m_robber_state = CantMoveRobber;
                emit robberPlaced(m_tiles[i]);
                break;
            }
    }

    this->update();
    QWidget::mousePressEvent(event);
}



QRectF MapWidget::robberRect(const QPointF& center)
{
    double r = m_size / 5;
    return QRectF(center - QPointF(r, r * 2.3), QSizeF(r * 2, r * 4));
}

void MapWidget::drawRobber(QPainter* painter, const QPointF& center, bool isTransparent)
{
    double r = m_size / 5;
    painter->setBrush(isTransparent ? QColor(192, 192, 192) : QColor(192, 192, 192));
    painter->drawEllipse(center, r, r * 1.5);
    painter->drawChord(QRectF(center - QPointF(r * 0.75, r * 2.25), QSizeF(r * 1.5, r * 1.5)), -30 * 16, 240 * 16);
    painter->drawRect(QRectF(center + QPointF(-r, r * 0.75), QSizeF(r * 2, r)));
}

void MapWidget::buildTiles()
{
    m_center = QPointF(this->width() / 2, this->height() / 2);
    m_size = min(this->height() / 8.0, this->width() / 5 / Const::SQRT3) * 0.8;

    if (!m_loaded) return;

    m_tiles[0]->SetGeometry(m_center + QPointF(-1 * Const::SQRT3 * m_size, -3 * m_size), m_size);
    m_tiles[1]->SetGeometry(m_center + QPointF(0 * Const::SQRT3 * m_size, -3 * m_size), m_size);
    m_tiles[2]->SetGeometry(m_center + QPointF(1 * Const::SQRT3 * m_size, -3 * m_size), m_size);

    m_tiles[3]->SetGeometry(m_center + QPointF(-1.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tiles[4]->SetGeometry(m_center + QPointF(-0.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tiles[5]->SetGeometry(m_center + QPointF(0.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);
    m_tiles[6]->SetGeometry(m_center + QPointF(1.5 * Const::SQRT3 * m_size, -1.5 * m_size), m_size);

    m_tiles[7]->SetGeometry(m_center + QPointF(-2 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[8]->SetGeometry(m_center + QPointF(-1 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[9]->SetGeometry(m_center + QPointF(0 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[10]->SetGeometry(m_center + QPointF(1 * Const::SQRT3 * m_size, 0), m_size);
    m_tiles[11]->SetGeometry(m_center + QPointF(2 * Const::SQRT3 * m_size, 0), m_size);

    m_tiles[12]->SetGeometry(m_center + QPointF(-1.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tiles[13]->SetGeometry(m_center + QPointF(-0.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tiles[14]->SetGeometry(m_center + QPointF(0.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);
    m_tiles[15]->SetGeometry(m_center + QPointF(1.5 * Const::SQRT3 * m_size, 1.5 * m_size), m_size);

    m_tiles[16]->SetGeometry(m_center + QPointF(-1 * Const::SQRT3 * m_size, 3 * m_size), m_size);
    m_tiles[17]->SetGeometry(m_center + QPointF(0 * Const::SQRT3 * m_size, 3 * m_size), m_size);
    m_tiles[18]->SetGeometry(m_center + QPointF(1 * Const::SQRT3 * m_size, 3 * m_size), m_size);

    /*for (int i = 0; i < Const::CITY_COUNT; i++)
        if (m_cities[i]) qDebug()<<i<<' '<<m_cities[i]->Point()<<' '<<m_cities[i]->State();*/
}

void MapWidget::Load(Const::Resource type[], int num[])
{
    m_loaded = true;
    bool hasRobber = false;
    for (int i = 0; i < Const::TILE_COUNT; i++)
    {
        m_tiles[i] = new Tile(type[i], num[i]);
        if (type[i] == Const::Desert && !hasRobber)
        {
            m_tiles[i]->SetRobberState(Tile::PlacedState);
            m_robber_tile = m_tiles[i];
            hasRobber = true;
        }
    }

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
            city->AddTile(m_tiles[i]);
        }
    }

    for (int i = 0, t = 0; i < Const::CITY_COUNT; i++)
        for (int j = i + 1; j < Const::CITY_COUNT; j++)
            if (m_cities[i]->Distance2(m_cities[j]->Point()) - Const::Sqr(m_size) < Const::EPS)
            {
                m_roads[t] = new Road(m_cities[i], m_cities[j]);
                m_cities[i]->AddRoad(m_roads[t]);
                m_cities[j]->AddRoad(m_roads[t]);
                t++;
            }
}

void MapWidget::ObtainResources(int number)
{
    int cnt[Const::RESOURCE_COUNT] = {0};
    for (int i = 0; i < Const::TILE_COUNT; i++)
        if (m_tiles[i]->Number() == number)
        {
            for (int j = 0; j < 6; j++)
                if (m_tiles[i]->GetRobberState() == Tile::NoneState && m_tiles[i]->CityAt(j)->OwnerId() == Player::Self()->Id())
                {
                    int x = m_tiles[i]->CityAt(j)->Type() == Building::CityType ? 2 : 1;
                    Player::Self()->ObtainResources(m_tiles[i]->Type(), x);
                    cnt[(size_t)m_tiles[i]->Type()] += x;
                }
        }
    emit obtainedResources(cnt);
}
