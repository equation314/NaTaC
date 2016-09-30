#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "player.h"

class GameInfo
{
public:
    // Getter member functions
    static int Round() { return s_round; }
    static QList<Player*> PlayerList() { return s_player_list; }

    // Setter member functions
    static void IncRound() { s_round++; }
    static void SetPlayerList(const QList<Player*>& list) { s_player_list = list; }

private:
    GameInfo() {}

    static int s_round;
    static QList<Player*> s_player_list;
};

#endif // GAMEINFO_H
