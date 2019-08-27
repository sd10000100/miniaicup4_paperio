#ifndef GAMESTATE_CPP
#define GAMESTATE_CPP
#include "gamestate.h"

#endif // GAMESTATE_CPP

    GameStage::GameStage(int _treshold){
        stage = 0;
        treshold = _treshold;
        startPosition={};
        tempPositions ={};
        countfSteps = 0;

    }

    void GameStage::Update(GameWorld world)
    {
        if(isPointOnTerritory(world.me.position[0], world.me.position[1], world.me, world))
        {
            this->stage=0;

            auto nearest = findNearestNotTerritoryCell(world.me.position[0], world.me.position[1],world);
            if(nearest[0]!=0 && nearest[1]!=0)
                this->nearestSpace = nearest;
            else {
                if(world.players.size()>0){
                    for(auto player: world.players)
                    {
                        if(isPlayerNearest(player.first,world))
                        {
                            this->nearestSpace = player.second.position;
                        }
                    }
                }
                else {
                    this->nearestSpace = {world.width*world.x_cells_count, world.width*world.y_cells_count};
                }
            }
        }

        // Если мы ищем откуда начать и стоим не у себя на территории
        if(this->stage==0 && !isPointOnTerritory(world.me.position[0], world.me.position[1], world.me, world))
        {
            this->stage=1;
            this->countfSteps = 0;
            this->startPosition = {world.me.position[0], world.me.position[1]};
            this->tempPositions.push_back({world.me.position[0], world.me.position[1]});
        }
        //идем подальше от своей территории
        if(this->stage==1 && (this->countfSteps)>this->treshold)
        {
            this->stage=2;
            this->countfSteps = 0;
            this->tempPositions.push_back({world.me.position[0], world.me.position[1]});
        }

        if(this->stage==2 && (this->countfSteps)>this->treshold){
            this->stage=3;
            this->countfSteps = 0;
            this->tempPositions.push_back({world.me.position[0], world.me.position[1]});
        }

        if(this->stage==3  && ((this->countfSteps)>this->treshold ))
        {
            this->stage = 4;
            this->countfSteps = 0;
            this->tempPositions.push_back({world.me.position[0], world.me.position[1]});
        }

        if((EnemyOnMyTerritory(world) || distToNearestEnemy(world)/30<=5) && this->stage!=0 )
        {
            this->stage = 4;
            this->countfSteps = 0;
            this->tempPositions.push_back({world.me.position[0], world.me.position[1]});
        }

        if(this->stage == 4 && isPointOnTerritory(world.me.position[0], world.me.position[1], world.me, world))
        {
            this->stage = 0;
            this->countfSteps = 0;
            this->startPosition = {};
            this->tempPositions = {};
            this->nearestSpace = findNearestNotTerritoryCell(world.me.position[0], world.me.position[1],world);
        }

    }

    void GameStage::UpdateTreshold(double nearestEnemyDist, GameWorld world)
    {
        if(nearestEnemyDist>=17)
            this->treshold = 4;
        else if(nearestEnemyDist<17 && nearestEnemyDist>=13)
            this->treshold = 3;
        else if(nearestEnemyDist<13 && nearestEnemyDist>=7)
            this->treshold = 2;
        else if(nearestEnemyDist<7)
            this->treshold = 1;
    }

