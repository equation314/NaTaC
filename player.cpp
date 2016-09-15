#include "player.h"
#include "building.h"

Player* Player::s_self = nullptr;
int Player::s_current_player_id = -1;

Player::Player(int id) :
    m_id(id), m_city_count(0), m_road_count(0), m_score(0)
{
    memset(m_resources, 0, sizeof(m_resources));
}

bool Player::CanbuildRoad() const
{
    if (m_road_count < Const::INITIAL_ROAD_COUNT) return true;
    for (int i = 0; i < Const::RESOURCES_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[0][i]) return false;
    return true;
}

bool Player::CanbuildVillage() const
{
    if (m_city_count < Const::INITIAL_ROAD_COUNT) return true;
    for (int i = 0; i < Const::RESOURCES_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[1][i]) return false;
    return true;
}

bool Player::CanbuildCity() const
{
    for (int i = 0; i < Const::RESOURCES_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[2][i]) return false;
    return true;
}

bool Player::CanUseDevelopmentCard() const
{
    for (int i = 0; i < Const::RESOURCES_COUNT; i++)
        if (m_resources[i] < Const::DEPEND[3][i]) return false;
    return true;
}

void Player::Build(Building* building)
{
    if (building->Type() == Building::RoadType)
        m_road_count++;
    else if (building->Type() == Building::VillageType)
        m_city_count++;

    if (m_road_count > Const::INITIAL_ROAD_COUNT || m_city_count > Const::INITIAL_CITY_COUNT)
    {
        for (int i = 0; i < Const::RESOURCES_COUNT; i++)
        {
            if (building->Type() == Building::RoadType)
                m_resources[i] -= Const::DEPEND[0][i];
            else if (building->Type() == Building::VillageType)
                m_resources[i] -= Const::DEPEND[1][i];
            else if (building->Type() == Building::CityType)
                m_resources[i] -= Const::DEPEND[2][i];
        }
    }
}
