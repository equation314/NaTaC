#ifndef BUILDING_H
#define BUILDING_H

#include <QColor>
#include <QPointF>

class Building
{
public:
    enum BuildingState
    {
        None,
        Hover,
        Level1,
        Level2
    };

    Building();

    // Getter member functions
    BuildingState State() const { return m_state; }
    QColor TransparentColor() const
    {
        QColor color = m_color;
        color.setAlpha(150);
        return color;
    }
    QColor Color() const { return m_color; }

    // Setter member functions
    void SetState(BuildingState state) { m_state = state; }
    QColor SetColor(const QColor& color) { m_color = color; }

protected:
    virtual bool Contains(const QPointF& point, double size) const = 0;

private:
    QColor m_color;
    BuildingState m_state;
};

#endif // BUILDING_H
