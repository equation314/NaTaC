#include "player.h"
#include "building.h"

Building::Building() :
    m_owner_id(-1), m_type(NoneType), m_state(None)
{

}

bool Building::Build()
{
    if (m_state == Hover) m_state = Built; else return false;
    if (m_type == VillageType) m_type = CityType;
    else if (Class() == CityClass) m_type = VillageType;
    else if (Class() == RoadClass)  m_type = RoadType;

    m_owner_id = Player::Self()->Id();
    Player::Self()->Build(this);
    return true;
}
