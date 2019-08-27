#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>

#include "helper.h"
#endif // GAMESTATE_H



using namespace std;

struct GameStage{
    GameStage(int _treshold = 0);
    vector<int> startPosition;
     vector<int> nearestSpace;
    vector<vector<int>> tempPositions;
    int stage;
    int treshold;
    int countfSteps;
    // 0 - поход к краю области за 1
    // 1 - намечаем область
    // 2 - расширение
    // 3 - укрепление
    // 4 - захват
    // 5 - аварийное отступление

    void Update(GameWorld world);

    void UpdateTreshold(double nearestEnemyDist, GameWorld world);
};
