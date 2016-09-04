#include "city.h"
#include "road.h"

#include <QDebug>

City::City(const QPointF& point) :
    m_point(point), m_road_count(0)
{

}

bool City::CanPlace() const
{
    if (this->Type() == CityType) return false;
    if (this->Type() == VillageType) return true;
    bool ok = false;
    for (int i = 0; i < m_road_count; i++)
    {
        if (m_roads[i]->Owner() == Player::CurrentPlayer()) ok = true;
        if (m_roads[i]->Start() != this && (m_roads[i]->Start()->IsBuilt())) return false;
        if (m_roads[i]->Start() != this && m_roads[i]->End()->IsBuilt()) return false;
    }
    if (Player::CurrentPlayer()->CityCount() < Const::INITIAL_CITY_COUNT)
        return true;
    return ok;
}
