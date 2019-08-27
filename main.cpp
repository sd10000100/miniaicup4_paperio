#include <iostream>
#include <string>
#include <time.h>
#include "solve.cpp"

using namespace std;


int main() {
    srand(time(0));
    string input_string, input_type, config;
    getline(cin, config);
    GameWorld world = GameWorld(nlohmann::json::parse(config));
    Solve solver = Solve(world);
    while (true && world.type!="end_game") {
        getline(cin, input_string);
        world.Update(nlohmann::json::parse(input_string));
        if(world.type == "tick"){
            nlohmann::json command;
            command["command"]=solver.GetNextAction(world);
            cout << command.dump() << endl;
         }else return 0;
   }
   return 0;
}
