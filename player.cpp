#include "player.h"
#include "building.h"

Player* Player::s_self = nullptr;
int Player::s_current_player_id = -1;

Player::Player(int id, const QString& name) :
    m_id(id), m_name(name), m_road_count(0), m_village_count(0), m_city_count(0), m_resource_count(0), m_score(0), m_is_ready(false)
{
    memset(m_resources, 0, sizeof(m_resources));
}

bool Player::CanbuildRoad() const
{
    if (m_road_count < Const::INITIAL_ROAD_COUNT) return true;
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[0][i]) return false;
    return true;
}

bool Player::CanbuildVillage() const
{
    if (m_village_count < Const::INITIAL_CITY_COUNT && !m_city_count) return true;
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[1][i]) return false;
    return true;
}

bool Player::CanbuildCity() const
{
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[2][i]) return false;
    return true;
}

bool Player::CanUseDevelopmentCard() const
{
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[3][i]) return false;
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

    if (m_road_count == Const::INITIAL_ROAD_COUNT && m_village_count == Const::INITIAL_CITY_COUNT && !m_city_count && !m_is_ready)
    {
        m_is_ready = true;
        emit ready();
    }
    if (m_road_count > Const::INITIAL_ROAD_COUNT || m_village_count > Const::INITIAL_CITY_COUNT || m_city_count)
    {
        for (int i = 0; i < Const::RESOURCE_COUNT; i++)
        {
            if (building->Type() == Building::RoadType)
            {
                m_resources[i] -= Const::DEPEND[0][i];
                m_resource_count -= Const::DEPEND[0][i];
            }
            else if (building->Type() == Building::VillageType)
            {
                m_resources[i] -= Const::DEPEND[1][i];
                m_resource_count -= Const::DEPEND[1][i];
            }
            else if (building->Type() == Building::CityType)
            {
                m_resources[i] -= Const::DEPEND[2][i];
                m_resource_count -= Const::DEPEND[2][i];
            }
        }
    }
}

void Player::BuyDevelopmentCard()
{
    for (int i = 0; i < Const::RESOURCE_COUNT; i++)
    {
        m_resources[i] -= Const::DEPEND[3][i];
        m_resource_count -= Const::DEPEND[3][i];
    }
}
