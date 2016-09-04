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
    Player* Owner() const { return m_owner; }
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
            return m_owner->Color();
        else
            return Player::CurrentPlayer()->Color();
    }

    // Setter member functions
    void SetState(BuildingState state) { m_state = state; }

    bool Build();

    virtual BuildingClass Class() const = 0;
    virtual bool CanPlace() const = 0;
    virtual bool Contains(const QPointF& point, double size) const = 0;

private:
    Player* m_owner;
    BuildingType m_type;
    BuildingState m_state;
};

#endif // BUILDING_H
