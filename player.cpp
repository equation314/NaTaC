#include "player.h"
#include "building.h"
#include "gameinfo.h"

#include <QDebug>

Player* Player::s_self = nullptr;
int Player::s_current_player_id = -1;

Player::Player(int id, const QString& name) :
    m_id(id), m_name(name), m_road_count(0), m_village_count(0), m_city_count(0), m_resource_count(0), m_score(0)
{
    memset(m_resources, 0, sizeof(m_resources));
}

bool Player::CanbuildRoad() const
{
    if (m_road_count < Const::INITIAL_ROAD_COUNT && m_road_count == m_village_count - 1) return true;
    if (!GameInfo::Round()) return false;
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::COST[0][i]) return false;
    return true;
}

bool Player::CanbuildVillage() const
{
    if (m_village_count < Const::INITIAL_CITY_COUNT && m_village_count == m_road_count && !m_city_count) return true;
    if (!GameInfo::Round()) return false;
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::COST[1][i]) return false;
    return true;
}

bool Player::CanbuildCity() const
{
    if (!GameInfo::Round()) return false;
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::COST[2][i]) return false;
    return true;
}

bool Player::CanUseDevelopmentCard() const
{
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::COST[3][i]) return false;
    return true;
}

void Player::Build(Building* building)
{
    switch (building->Type())
    {
    case Building::RoadType:
        m_road_count++;
        break;
    case Building::VillageType:
        m_village_count++;
        m_score++;
        break;
    case Building::CityType:
        m_village_count--;
        m_city_count++;
        m_score++;
        break;
    default:
        break;
    }

    if (m_road_count > Const::INITIAL_ROAD_COUNT || m_village_count > Const::INITIAL_CITY_COUNT || m_city_count)
    {
        for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        {
            if (building->Type() == Building::RoadType)
            {
                m_resources[i] -= Const::COST[0][i];
                m_resource_count -= Const::COST[0][i];
            }
            else if (building->Type() == Building::VillageType)
            {
                m_resources[i] -= Const::COST[1][i];
                m_resource_count -= Const::COST[1][i];
            }
            else if (building->Type() == Building::CityType)
            {
                m_resources[i] -= Const::COST[2][i];
                m_resource_count -= Const::COST[2][i];
            }
        }
    }
}

void Player::BuyDevelopmentCard()
{
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
    {
        m_resources[i] -= Const::COST[3][i];
        m_resource_count -= Const::COST[3][i];
    }
}
