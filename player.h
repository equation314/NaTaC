#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"

class Building;
class Player
{
public:
    static Player* Self() { return s_self; }
    static void SetSelf(Player* player) { s_self = player; }
    static int CurrentPlayerId() { return s_current_player_id; }
    static void SetCurrentPlayerId(int id) { s_current_player_id = id; }

    explicit Player(int id);
    ~Player() {}

    // Getter member functions
    int Id() const { return m_id; }
    int CityCount() const { return m_city_count; }
    int RoadCount() const { return m_road_count; }
    int ResourceAt(int i) const { return m_resources[i]; }
    QColor Color() const { return Const::PLAYER_COLOR[m_id]; }

    bool CanbuildRoad() const;
    bool CanbuildVillage() const;
    bool CanbuildCity() const;
    bool CanUseDevelopmentCard() const;
    void Build(Building* building);

private:
    static Player* s_self;
    static int s_current_player_id;

    int m_id;
    int m_city_count, m_road_count, m_score;
    int m_resources[Const::RESOURCES_COUNT];
};

#endif // PLAYER_H
