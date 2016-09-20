#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"

#include <QObject>

class Building;
class Player : public QObject
{
    Q_OBJECT

public:
    static Player* Self() { return s_self; }
    static void SetSelf(Player* player) { s_self = player; }
    static int CurrentPlayerId() { return s_current_player_id; }
    static void SetCurrentPlayerId(int id) { s_current_player_id = id; }

    explicit Player(int id, const QString& name);
    ~Player() {}

    // Getter member functions
    int Id() const { return m_id; }
    QString Name() const { return m_name; }
    QString ColorName() const { return QString("<span style=\"color:%1\">%2</span>").arg(Color().name()).arg(m_name); }
    int Score() const { return m_score; }
    int RoadCount() const { return m_road_count; }
    int VillageCount() const { return m_village_count; }
    int CityCount() const { return m_city_count; }
    int CityClassCount() const { return m_village_count + m_city_count; }
    int ResourceAt(int i) const { return m_resources[i]; }
    QColor Color() const { return Const::PLAYER_COLOR[m_id]; }

    bool CanbuildRoad() const;
    bool CanbuildVillage() const;
    bool CanbuildCity() const;
    bool CanUseDevelopmentCard() const;

    void Build(Building* building);
    void ObtainResources(Const::Resource type, int num) { m_resources[(size_t)type] += num; }

private:
    static Player* s_self;
    static int s_current_player_id;

    int m_id;
    QString m_name;
    int m_road_count, m_village_count, m_city_count, m_score;
    int m_resources[Const::RESOURCE_COUNT];
    bool m_is_ready;

signals:
    void ready();
};

#endif // PLAYER_H
