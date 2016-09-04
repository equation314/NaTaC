#include "player.h"
#include "building.h"

Player* Player::m_current_player = nullptr;

Player::Player(int id) :
    m_id(id), m_city_count(0), m_road_count(0)
{

}

void Player::Build(Building *building)
{
    if (building->Type() == Building::VillageType)
        m_city_count++;
    else if (building->Type() == Building::RoadType)
        m_road_count++;
}
