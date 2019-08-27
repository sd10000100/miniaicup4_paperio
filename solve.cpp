//#include "../nlohmann/json.hpp"
//#include <iostream>
#include <string>
#include "gamestate.h"
#include "graphcell.cpp"


static map <string,vector<string>> DIR_MAP = {{ "l", {"l","d", "u" } },
                                 { "r", {"r","u",  "d"} },
                                 { "u", {"u", "l", "r"} },
                                 { "", {"l","u", "r", "d"} },
                                 { "d", {"d","r",  "l"} }};

static map <string,string> DIR_SHORT_MAP = {{ "l", "left"},
                                        { "r", "right"},
                                        { "u", "up" },
                                        { "d", "down"}};

static map <string,string> DIR_SHORT_MAP_REVERT = {{ "left", "l"},
                                        { "right", "r"},
                                        { "up", "u" },
                                        { "down", "d"}};


class Solver
{
public:
    virtual ~Solver() { }
    virtual string GetNextAction(GameWorld world) = 0;
};


struct Solve:Solver{
    Solve(GameWorld world)
    {
        state = GameStage(1);
    }


    //// TODO: вынести это вот все в отдельный файл
    //bool isNewLineOnTerritory(int next_x, int next_y,Player player, GameWorld world)
    //{
    ////    int next_x = cell.position[0];
    ////    int next_y = cell.position[1];
    //    for (auto line : player.territory)
    //    {
    //      if((abs(line[0] - next_x)<world.width/2 && abs(line[1] - next_y)<world.width/2))
    //      {
    //          return true;
    //      }
    //    }
    //    return false;
    //}

    //bool isEnemyOnThisCellAndMyTailIsLonger(GraphCell cell,GameWorld world){
    //    for(auto player : world.players){
    //        int enemyPosX = player.second.position[0];
    //        int enemyPosY = player.second.position[1];
    //        for(int i=0 ; i<cell.direction.length();i++)
    //        {
    //            if(player.second.direction == "left")
    //                enemyPosX = enemyPosX-30;
    //            else if(player.second.direction == "right")
    //                enemyPosX = enemyPosX+30;
    //            else if(player.second.direction == "up")
    //                enemyPosY =enemyPosY+30;
    //            else if(player.second.direction == "down")
    //                enemyPosY= enemyPosY-30;
    //        }

    //        if((abs(cell.position[0] - enemyPosX)<world.width/2 && abs(cell.position[1] - enemyPosY)<world.width/2) && world.me.lines.size()>player.second.lines.size())
    //        {
    //            //ктото наступил мне на хвост
    //            return true;
    //        }
    //    }
    //    return false;
    //}


    //bool isEnemySteppedOnMyTail(GraphCell cell,GameWorld world)
    //{
    //    for(auto player : world.players){
    //        int enemyPosX = player.second.position[0];
    //        int enemyPosY = player.second.position[1];
    //        for(int i=0 ; i<cell.direction.length();i++)
    //        {
    //            if(player.second.direction == "left")
    //                enemyPosX = enemyPosX-30;
    //            else if(player.second.direction == "right")
    //                enemyPosX = enemyPosX+30;
    //            else if(player.second.direction == "up")
    //                enemyPosY =enemyPosY+30;
    //            else if(player.second.direction == "down")
    //                enemyPosY= enemyPosY-30;
    //        }
    //        auto myNewLine = world.me.lines;
    //        for(auto item : cell.path)
    //        {
    //            myNewLine.push_back(item);
    //        }
    //        for (auto line : myNewLine)
    //        {
    //          if((abs(line[0] - enemyPosX)<world.width/2 && abs(line[1] - enemyPosY)<world.width/2))
    //          {
    //              //ктото наступил мне на хвост
    //              return true;
    //          }
    //        }

    //    }
    //    return false;
    //}


    //bool isEnemyOnMyTerritory(GraphCell cell,GameWorld world)
    //{
    //    for(auto player : world.players){
    //        int enemyPosX = player.second.position[0];
    //        int enemyPosY = player.second.position[1];
    //        for(int i=0 ; i<cell.direction.length();i++)
    //        {
    //            if(player.second.direction == "left")
    //                enemyPosX = enemyPosX-30;
    //            else if(player.second.direction == "right")
    //                enemyPosX = enemyPosX+30;
    //            else if(player.second.direction == "up")
    //                enemyPosY =enemyPosY+30;
    //            else if(player.second.direction == "down")
    //                enemyPosY= enemyPosY-30;
    //        }
    //        auto myNewLine = world.me.lines;
    //        for(auto item : cell.path)
    //        {
    //            myNewLine.push_back(item);
    //        }
    //        for (auto line : myNewLine)
    //        {
    //          if((abs(line[0] - enemyPosX)<world.width/2 && abs(line[1] - enemyPosY)<world.width/2))
    //          {
    //              //ктото наступил мне на хвост
    //              return true;
    //          }
    //        }

    //    }
    //    return false;
    //}
    //// TODO: вынести это вот все в отдельный файл



    // метод для отсечения краев и своего хвоста =)



    bool isSpaceOnMyTerritory(Player player, const GameWorld world)
    {
        for(auto line : player.lines)
        {
            if(isPointOnTerritory(line[0],line[1],world.me,world))
                return true;
        }
        return false;
    }



    double FindPositiveWeight(GraphCell cell, GraphCell parent,const GameWorld world, GameStage &state)
    {
        int next_x = cell.position[0];
        int next_y = cell.position[1];
        double res = cell.positiveWeight;

        // TODO: Проверять расположение врага к этому моменту

        if(state.stage==0)
        {

            if(EnemyOnMyTerritory(world)) //|| EnemyTailOnMyTerritory(world)
            {

                for(auto player: world.players)
                {
                  if(isPointOnTerritory(player.second.position[0], player.second.position[1], world.me, world))
                  {
                      res=1/distToPoint(next_x, next_y,player.second.position[0], player.second.position[1]);

                      if((abs(player.second.position[0] - next_x)<world.width/2 && abs(player.second.position[1] - next_y)<world.width/2))
                      {
                          res*=1000.0;
                      }
                      else
                      {
                          for(auto line: player.second.lines)
                          {
                              if((abs(line[0] - next_x)<world.width/2 && abs(line[1] - next_y)<world.width/2))
                              {
                                  res*=500.0;
                              }
                          }
                      }
                  }
                  else if(IsPlayerTailOnMyTerritory(player.second,world))
                  {
                      res=1/distToPlayerTail(next_x, next_y,player.second,world);
                      for(auto line: player.second.lines)
                      {
                          if((abs(line[0] - next_x)<world.width/2 && abs(line[1] - next_y)<world.width/2))
                          {
                              res*=500.0;
                          }
                      }
                  }
                }

            }
            else {
                //TODO: проверять шлейф врага на своей территории
                vector<int> cell = state.nearestSpace;// findNearestNotTerritoryCell(world.me.position[0], world.me.position[1],world, state);
               // cerr<<"findNearestNotTerritoryCell ["<< world.me.position[0]<<","<<world.me.position[1]<<"] res ["<<cell[0]<<","<< cell[1]<<"]"<<endl;
                double dist = distToPoint(next_x, next_y, cell[0], cell[1]);
                res = 30/dist;
                if(distToNearestTail(world) > distToNearestEnemy(world))
                {
                    res = res/distToNearestTail(world);
                    if(distToNearestEnemy(world)/30.0<2)
                    {
                        for(auto player: world.players)
                        {
                            if(isPlayerNearest(player.first,world))
                            {
                              if((abs(player.second.position[0] - next_x)<world.width/2 && abs(player.second.position[1] - next_y)<world.width/2) && world.me.lines.size()<player.second.lines.size())
                              {
                                  res*=1000.0;
                              }
                              else if ((abs(player.second.position[0] - next_x)<world.width/2 && abs(player.second.position[1] - next_y)<world.width/2) && world.me.lines.size()>player.second.lines.size())
                              {
                                  res/=1000.0;
                              }
                            }

                        }

                    }
                    else {
                        for(auto player: world.players)
                        {
                            if(isPointOnMyTail(next_x,next_y,player.second, world))
        //                    if(isPlayerNearest(player.first,world))
        //                    {
        //                      if((abs(player.second.position[0] - next_x)<world.width/2 && abs(player.second.position[1] - next_y)<world.width/2) && world.me.lines.size()<player.second.lines.size())
        //                      {
                                  res*=1000.0;
        //                      }
        //                      else if ((abs(player.second.position[0] - next_x)<world.width/2 && abs(player.second.position[1] - next_y)<world.width/2) && world.me.lines.size()>player.second.lines.size())
        //                      {
        //                          res/=1000.0;
        //                      }
        //                    }

                        }
                    }
                }
            }


        }

        if(state.stage==1)
        {

            // почему 0?
            res = distToMyTerritory(next_x, next_y, world);

           for(auto player: world.players)
           {
             if(isPointOnTerritory(player.second.position[0], player.second.position[1], player.second, world) &&  isPointOnTerritory(next_x, next_y, player.second, world))
             {
                 res=0;
             }
             else if(distToPoint(next_x, next_y, player.second.position[0], player.second.position[1])/30.0>2+distToPlayerTail(next_x, next_y,player.second,world)/30.0)
             {
                 if(isPointOnMyTail(next_x, next_y, player.second,world))
                     res*=1000;
                 else res*=500;
             }
           }
        }

        if(state.stage==2)
        {
            // почему 0?
            state.stage=3;
        }

        if(state.stage==3)
        {
            // почему 0?
            vector<vector<int>> temp = {};
            for(auto line : state.tempPositions)
            {
                temp.push_back({line[0],line[1]});
            }
            //vector<int> temp = state.tempPositions[state.tempPositions.size()-1];
            temp.push_back({next_x, next_y});
            res = SGauss(temp);

        }

        if(state.stage==4)
        {
            double temp1 = distToMyTerritory(next_x, next_y, world);
            double temp2 = distToMyTerritory(world.me.position[0], world.me.position[1], world);
            if(temp1<temp2)
                res = 1/temp1;
            else {
                res=1/temp2;
            }
            if(isPointOnTerritory(next_x, next_y, world.me, world))
            {
                res = 100;
            }
        }

        for (auto bonus : world.bonuses)
        {
           // cerr<<bonus.type<<endl;
            if((bonus.type=="saw" || bonus.type=="n") && (abs(bonus.position[0] - next_x)<world.width/2 && abs(bonus.position[1] - next_y)<world.width/2))
            {
                res *= 2000;
            }
            else if(bonus.type=="s" && (abs(bonus.position[0] - next_x)<world.width/2 && abs(bonus.position[1] - next_y)<world.width/2))
                res /= 100;
        }

        if(state.stage>=1 && state.stage<=3)
        {



        for(auto player : world.players){
            if(isPointOnTerritory(next_x, next_y, player.second, world))
            {
                res = res*100;
            }
            else {

            }

            if(isPlayerNearest(player.first,world)){
                //cerr<<player.first<<endl;
                int enemyPosX = player.second.position[0];
                int enemyPosY = player.second.position[1];
                for(int i=0 ; i<cell.direction.length();i++)
                {
                    if(player.second.direction == "left")
                        enemyPosX = enemyPosX-30;
                    else if(player.second.direction == "right")
                        enemyPosX = enemyPosX+30;
                    else if(player.second.direction == "up")
                        enemyPosY =enemyPosY+30;
                    else if(player.second.direction == "down")
                        enemyPosY= enemyPosY-30;
                    player.second.lines.push_back({enemyPosX,enemyPosY} );
                }
                double dist1 = distToPoint(next_x, next_y,enemyPosX,enemyPosY );
                double dist2 = distToPlayerTail(next_x, next_y,player.second,world);


                if((abs(enemyPosX - next_x)<world.width/2 && abs(enemyPosY - next_y)<world.width/2) && world.me.lines.size()<player.second.lines.size()) //&& isPointOnMyTail(next_x, next_y,world.me,world)
                {
                    res=res*3;
                }
                else if(isPointOnMyTail(next_x,next_y,player.second,world))
                {
                    res=res*3;
                }
                else {

                    res=res/10;
                }
                for(int i=0 ; i<cell.direction.length();i++)
                {
                    player.second.lines.pop_back();
                }
            }

            if(isPointOnTerritory(player.second.position[0], player.second.position[1], player.second, world) &&  isPointOnTerritory(next_x, next_y, player.second, world))
            {
                res=0;
            }
            else if(distToPoint(next_x, next_y, player.second.position[0], player.second.position[1])/30.0>2+distToPlayerTail(next_x, next_y,player.second,world)/30.0)
            {
                if(isPointOnMyTail(next_x, next_y, player.second,world))
                    res*=1000;
                else res*=500;
            }


        }


    }


        // всякенькие штрафы (убрать?)
        if(distToMyTerritory(next_x,next_y,world)/30>state.treshold*sqrt(2))
        {
            res=res/(double)(distToMyTerritory(next_x,next_y,world)/30-state.treshold*sqrt(2));
        }

        if(world.me.lines.size()+cell.direction.size()>2*state.treshold)
        {
            double temp = (double)state.treshold/(double)(world.me.lines.size()+cell.direction.size());
            res=res*temp;
        }


        return res;
    }




    void PositionInVertexAndBetter(GraphCell cell, vector<GraphCell> &vertexes,const  GameWorld world)
    {
        for(GraphCell &line : vertexes)
        {
            if((abs(line.position[0] - cell.position[0])<world.width/2 && abs(line.position[1] - cell.position[1])<world.width/2))
            {
                if(cell.positiveWeight>line.positiveWeight && cell.direction.size()<=line.direction.size())
                {
                    line = cell;
                }
            }
        }
    }

    vector<GraphCell> subprocess(int maxN,int N, GraphCell cell, vector<GraphCell> vertexes,const  GameWorld world, GameStage &state)
    {
        if(N>=1)
        {
            for(auto item : DIR_MAP[cell.current])
            {
                GraphCell cellNew = GraphCell();
                vector<int> current = {};
                if(item == "l")
                    current = {cell.position[0]-30,cell.position[1] };
                else if(item == "r")
                    current = {cell.position[0]+30,cell.position[1] };
                else if(item == "u")
                    current = {cell.position[0],cell.position[1]+30 };
                else if(item == "d")
                    current = {cell.position[0],cell.position[1]-30 };
                cellNew.direction = cell.direction+item;
                cellNew.path = cell.path;
                cellNew.level = N;
                cellNew.path.push_back(current);

                cellNew.position = current;

                cellNew.potential = 0.0;//SGauss(cell.path);

                cellNew.current = item;
                cellNew.positiveWeight = FindPositiveWeight(cellNew,cell, world,state);
                cellNew.weight = FindWeight(cellNew, world,state);
                // TODO: отсекать тупиковые пути
                if(cellNew.weight>0)
                {
                    PositionInVertexAndBetter(cellNew, vertexes,world);
                    vertexes.push_back(cellNew);
                    vertexes = subprocess(maxN, N-1, cellNew, vertexes, world,state);
                }

            }


        }
        return vertexes;
    }

    double FindWeight(GraphCell cell,GameWorld world, GameStage &state)
    {
        int next_x = cell.position[0];
        int next_y = cell.position[1];
        double res = cell.weight+ rand()%10+1;


        if( (next_x<0 || next_x>world.x_cells_count*world.width || next_y<0 || next_y>world.y_cells_count*world.width))
        {
            return -1;
        }

        for (auto line : world.me.lines)
        {
          if((abs(line[0] - next_x)<world.width/2 && abs(line[1] - next_y)<world.width/2))
          {
              return -1;
          }
        }
        return res;
    }


    // завести класс для решения задачи
    // интерфейсы?

    vector<GraphCell> process(int stepCount, const GameWorld world, GameStage &state)
    {
        vector<GraphCell> vertexes = {};
        state.Update(world);
        GraphCell cell = GraphCell();
        cell.path  = {};
        cell.direction ="";
        cell.weight=0;
        cell.level = stepCount;
        cell.position = world.me.position;
        cell.current=DIR_SHORT_MAP_REVERT[world.me.direction];
        vertexes = subprocess(stepCount, stepCount, cell, vertexes, world,state);
        return vertexes;
    }

    string GetNextAction(GameWorld world)
    {
                    double nearestEnemy = distToNearestEnemy(world)/(double)world.width;
                    double nearestToMyTailEnemy = distToNearestToMyTailEnemy(world)/(double)world.width;
                    //cerr<<"nearestEnemy "<<nearestEnemy<<endl;

                    state.UpdateTreshold(min(nearestEnemy,nearestToMyTailEnemy),world);
                    //stateGame.treshold = 0.5;
                    vector<GraphCell> vertexes = {};
                    vertexes = process(4, world,state);
                    string next_step = "l";
                    vector<int> targetPos = {};
                    double max = -1;
                        for (auto line : vertexes)
                        {
                            if (line.positiveWeight>max)
                            {
                                max = line.positiveWeight;
                                next_step = line.direction[0];
                                targetPos = line.position;
                            }
                        //if (stateGame.stage==0)
                        //  cerr<<"Graph = "<<line.current<< " "<<line.direction<<" potential - "<<line.potential<<" positive -  "<<line.positiveWeight<<endl;

                        }

                        int min = 10000;
                        for (auto line : vertexes)
                        {
                            if (line.positiveWeight==max && targetPos[0]==line.position[0] && targetPos[1]==line.position[1] && line.direction.size()<min)
                            {
                                min = line.direction.size();
                                next_step = line.direction[0];
                            }
                        }
                        cerr << "from "<<world.me.direction<<" to "<<" - "<<next_step<<" stage "<<state.stage<<endl;
                        state.countfSteps+=1;
                        return DIR_SHORT_MAP[next_step];
//                    if(world.type == "tick"){
//                        nlohmann::json command;
//                        command["command"]=DIR_SHORT_MAP[next_step];
//                        stateGame.countfSteps+=1;
//                        //cerr << "from "<<world.me.direction<<" to "<<next_step<<" - "<<command.dump()<<" stage "<<stateGame.stage<<endl;
//                        cout << command.dump() << endl;
//                    }



       // return "l";
    };

    GameStage state;
};
