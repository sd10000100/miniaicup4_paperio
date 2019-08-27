
#include <string>
#include <iostream>
#include "gameworld.h"
#include <map>

using namespace std;

    GameWorld::GameWorld(const nlohmann::json& config){
        type = config["type"].get<std::string>();
        auto params = config["params"];

        x_cells_count = params["x_cells_count"].get<int>();
        y_cells_count = params["y_cells_count"].get<int>();
        speed = params["speed"].get<int>();
        width = params["width"].get<int>();
    }

    void GameWorld::Update(const nlohmann::json& config) {
        type = config["type"].get<std::string>();
        auto params = config["params"];
        auto players_json = params["players"];
        try{

            players = {};
            for (auto& element : nlohmann::json::iterator_wrapper(players_json)) {

                if(element.key()=="i")
                    me = Player(element.value());
                else {
                    players[element.key()] = Player(element.value());
                }
            }
        }
        catch(nlohmann::json::exception& e)
        {
          //  cerr << "ERROR in Parse World players " <<  endl;
          //  cerr << "message: " << e.what() << '\n' << "exception id: " << e.id <<  endl;
        }
        try{
            auto bonuses_json = params["bonuses"];
            bonuses = {};


            for (auto& element : bonuses_json) {
                            //cerr<<element<<endl;
                          bonuses.push_back(Bonus(element));
                       }
        }
        catch(nlohmann::json::exception& e)
        {
            //cerr << "ERROR in Parse World bonuses " <<  endl;
           // cerr << "message: " << e.what() << '\n' << "exception id: " << e.id <<  endl;
        }
    }

