#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "bonus.h"

#endif // PLAYER_H

using namespace std;

struct Player{
    Player();
    Player(const nlohmann::json& config);

    int score; // — количество очков игрока
    vector<vector<int>> territory; // — массив координат клеток, принадлежащих территории игрока
    vector<int> position; // — текущее положение игрока
    vector<vector<int>> lines; // — массив координат клеток шлейфа
    vector<Bonus> bonuses; // — массив активных бонусов игрока
    string direction;
        //    type; // — тип бонуса ('n' - Ускорение (Нитро), 's' - Замедление, 'saw' - Пила)
        //    ticks; // — сколько еще клеток будет активен бонус
    //direction — направление движения игрока ("left", "right", "up", "down")
};
