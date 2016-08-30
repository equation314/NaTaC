#include "player.h"
#include "building.h"

Building::Building() :
    m_owner(nullptr), m_state(None)
{

}

bool Building::Build()
{
    if (m_state == Hover)
        m_state = Level1;
    else if (m_state == Level1 && MaxLevel() > Level1)
        m_state = Level2;
    else
        return false;
    m_owner = Player::CurrentPlayer();
    m_owner->Build(this);
    return true;
}
