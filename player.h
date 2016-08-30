#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"

class Building;
class Player
{
public:
    static Player* CurrentPlayer() { return m_current_player; }
    static int CurrentPlayerId() { return m_current_player->Id(); }
    static void SetCurrentPlayer(Player* player) { m_current_player = player; }

    explicit Player(int id);
    ~Player() {}

    // Getter member functions
    int Id() const { return m_id; }
    int CityCount() const { return m_city_count; }
    int RoadCount() const { return m_road_count; }
    QColor Color() const { return Const::PLAYER_COLOR[m_id]; }

    // Setter member functions

    void Build(Building* building);


private:
    static Player* m_current_player;

    int m_id;
    int m_city_count, m_road_count;
};

#endif // PLAYER_H
