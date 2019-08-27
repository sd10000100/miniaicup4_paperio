#include "bonus.h"
using namespace std;

    Bonus::Bonus(){}
    Bonus::Bonus(const nlohmann::json& config){
        type = config["type"].get<string>();
        position = config["position"].get<vector<int>>();
    }
