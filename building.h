#ifndef BUILDING_H
#define BUILDING_H

#include "const.h"
#include "player.h"

#include <QColor>
#include <QPointF>

class Road;
class City;
class Building
{
public:
    enum BuildingType { NoneType, RoadType, VillageType, CityType };
    enum BuildingClass { RoadClass, CityClass };
    enum BuildingState
    {
        None,
        Hover,
        Built
    };

    Building();
    virtual ~Building() {}

    // Getter member functions
    int OwnerId() const { return m_owner_id; }
    BuildingType Type() const { return m_type; }
    BuildingState State() const { return m_state; }
    bool IsBuilt() const { return m_state == BuildingState::Built || m_type != NoneType; }
    QColor TransparentColor() const
    {
        QColor color = Color();
        color.setAlpha(150);
        return color;
    }
    QColor Color() const
    {
        if (IsBuilt())
            return Const::PLAYER_COLOR[m_owner_id];
        else
            return Player::Self()->Color();
    }

    // Setter member functions
    void SetState(BuildingState state) { m_state = state; }

    bool Build();

    virtual BuildingClass Class() const = 0;
    virtual bool CanPlace() const = 0;
    virtual bool Contains(const QPointF& point, double size) const = 0;

private:
    int m_owner_id;
    BuildingType m_type;
    BuildingState m_state;
};

#endif // BUILDING_H
