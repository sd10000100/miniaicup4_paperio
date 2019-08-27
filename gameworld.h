#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <string>
#include <iostream>
#include "../nlohmann/json.hpp"
#include "player.h"
#include <map>

#endif // GAMEWORLD_H

using namespace std;


struct GameWorld{
    GameWorld(const nlohmann::json& config);

    void Update(const nlohmann::json& config);

    string type;
    int x_cells_count; // — количество элементарных ячеек по оси x
    int y_cells_count; // — количество элементарных ячеек по оси y
    int speed; // — скорость игрока
    int width; // — ширина и высота элементарной ячейки

    map<string, Player> players;
    vector<Bonus> bonuses;

    Player me;

    //    players; // — словарь, где ключ - идентификатор игрока, а значение - его состояние. Ключ - это либо id противника (случайное и постоянное для данной игры число), либо строка 'i' - идентификатор данного игрока. Формат состояния:
    //    score; // — количество очков игрока
    //    territory; // — массив координат клеток, принадлежащих территории игрока
    //    position; // — текущее положение игрока
    //    lines; // — массив координат клеток шлейфа
    //    bonuses; // — массив активных бонусов игрока
    //    type; // — тип бонуса ('n' - Ускорение (Нитро), 's' - Замедление, 'saw' - Пила)
    //    ticks; // — сколько еще клеток будет активен бонус
    //    bonuses; // — массив бонусов, расположенных на карте
    //    type; // — тип бонуса ('n' - Ускорение (Нитро), 's' - Замедление, 'saw' - пила)
    //    position; // — координаты бонуса, массив из двух элементов - (x, y)
    int tick_num; // — номер тика
};

