#ifndef BONUS_H
#define BONUS_H

#include "../nlohmann/json.hpp"
#include <vector>

#endif // BONUS_H



using namespace std;

struct Bonus{
    Bonus();
    Bonus(const nlohmann::json& config);
    string type; // — тип бонуса ('n' - Ускорение (Нитро), 's' - Замедление, 'saw' - пила)
    vector<int> position; // — координаты бонуса, массив из двух элементов - (x, y)
    int tick;
};
