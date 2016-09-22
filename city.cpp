#include "city.h"
#include "road.h"

#include <QDebug>

City::City(const QPointF& point) :
    m_point(point), m_tile_count(0), m_road_count(0)
{
    memset(m_tiles, 0, sizeof(m_tiles));
    memset(m_roads, 0, sizeof(m_roads));
}

bool City::CanPlace() const
{
    if (this->Type() == CityType) return false;
    if (this->Type() == VillageType) return true;
    bool ok = false;
    for (int i = 0; i < m_road_count; i++)
    {
        if (m_roads[i]->OwnerId() == Player::Self()->Id()) ok = true;
        if (m_roads[i]->Start() != this && m_roads[i]->Start()->IsBuilt()) return false;
        if (m_roads[i]->End() != this && m_roads[i]->End()->IsBuilt()) return false;
    }
    if (!Player::Self()->isReady()) return true;
    return ok;
}
