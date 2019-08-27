#include <string>
#include <vector>

using namespace std;

struct GraphCell{
    GraphCell(){
        weight = 0;
        positiveWeight = 0;
        negativeWeight = 0;
        direction = ' ';
        path={};
        level = 0;
        potential = 0;
    }
    vector<vector<int>> path;
    vector<int> position;
    int level;
    double weight;
    double potential;
    double positiveWeight;
    double negativeWeight;
    string current;
    string direction;
};
