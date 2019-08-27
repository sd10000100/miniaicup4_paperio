#include <iostream>
#include "player.h"
using namespace std;

    Player::Player(){}
    Player::Player(const nlohmann::json& config){
        try{
            score = config["score"].get<int>();
            territory = config["territory"].get<vector<vector<int>>>();
            position = config["position"].get<vector<int>>();
            direction = config["direction"].get<string>();
            lines = config["lines"].get<vector<vector<int>>>();
            auto bonusItems = config["bonuses"];
            bonuses = {};
        }
        catch(nlohmann::json::exception& e)
        {
          //  cerr << "ERROR in Parse Player " <<  endl;
          //  cerr << "message: " << e.what() << '\n' << "exception id: " << e.id <<  endl;
        }

    }

        //    int score; // — количество очков игрока
        //    vector<vector<int>> territory; // — массив координат клеток, принадлежащих территории игрока
        //    vector<int> position; // — текущее положение игрока
        //    vector<vector<int>> lines; // — массив координат клеток шлейфа
        //    vector<Bonus> bonuses; // — массив активных бонусов игрока
        //    string direction;
        //    type; // — тип бонуса ('n' - Ускорение (Нитро), 's' - Замедление, 'saw' - Пила)
        //    ticks; // — сколько еще клеток будет активен бонус
        //    direction — направление движения игрока ("left", "right", "up", "down")

