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
    enum BuildingType { CityType, RoadType };
    enum BuildingState
    {
        None,
        Hover,
        Level1,
        Level2
    };

    Building();
    virtual ~Building() {}

    // Getter member functions
    Player* Owner() const { return m_owner; }
    BuildingState State() const { return m_state; }
    bool IsBuilt() const { return m_state >= BuildingState::Level1; }
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

    virtual BuildingType Type() const = 0;
    virtual BuildingState MaxLevel() const = 0;
    virtual bool CanPlace() const = 0;
    virtual bool Contains(const QPointF& point, double size) const = 0;

private:
    Player* m_owner;
    BuildingState m_state;
};

#endif // BUILDING_H
