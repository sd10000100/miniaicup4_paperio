


#ifndef helper
#define helper

#include "gameworld.h"

#endif // helper



// TODO: вынести это вот все в отдельный файл
inline bool isPointOnTerritory(int x, int y, Player player, GameWorld world)
{
    for (auto line : player.territory)
    {
      if((abs(line[0] - x)<world.width/2 && abs(line[1] - y)<world.width/2))
      {
          return true;
      }
    }
    return false;
}


inline bool isPointOnMyTail(int x, int y,Player player,GameWorld world)
{

    for(auto line : player.lines)
    {
        if((abs(line[0] - x)<world.width/2 && abs(line[1] - y)<world.width/2))
        {
            return true;
        }
    }
    return false;
}


inline double distToPoint(int x, int y, int target_x, int target_y)
{
    return sqrt((x-target_x)*(x-target_x)+(y-target_y)*(y-target_y));

}

inline double distToMyTerritory(int x, int y, GameWorld world)
{
    double min = 100000.0;

    for(auto line :world.me.territory)
    {
        double temp = distToPoint(x,y, line[0],line[1]);
        if(temp<min)
            min = temp;
    }

    return min;
}

inline double distToMyTail(int x, int y, GameWorld world)
{
    double min = 100000.0;

    for(auto line :world.me.lines)
    {
        double temp = distToPoint(x,y, line[0],line[1]);
        if(temp<min)
            min = temp;
    }

    return min;
}

inline double distToPlayerTail(int x, int y,Player player, GameWorld world)
{
    double min = 100000.0;

    for(auto line :player.lines)
    {
        double temp = distToPoint(x,y, line[0],line[1]);
        if(temp<min)
            min = temp;
    }

    return min;
}

inline double distToPlayerTerritory(int x, int y,Player player, GameWorld world)
{
    double min = 100000.0;

    for(auto line :player.territory)
    {
        double temp = distToPoint(x,y, line[0],line[1]);
        if(temp<min)
            min = temp;
    }

    return min;
}


inline double distToNearestEnemy(GameWorld world)
{
    double min =  100000.0;
    for(auto player :world.players)
    {
        double temp = distToPoint(world.me.position[0],world.me.position[1], player.second.position[0],player.second.position[1]);
        if(temp<min)
            min = temp;
    }
    return min;
}


inline double distToNearestEnemyTerritory(int x, int y,GameWorld world)
{
    double min =  100000.0;
    for(auto player :world.players)
    {
        double temp = distToPlayerTerritory(x,y, player.second,world);
        if(temp<min)
            min = temp;
    }
    return min;
}

inline double distToNearestTail(GameWorld world)
{
    double min =  100000.0;
    for(auto player :world.players)
    {
        double temp = distToPlayerTail(world.me.position[0],world.me.position[1], player.second,world);
        if(temp<min)
            min = temp;
    }
    return min;
}

inline double distToNearestToMyTailEnemy(GameWorld world)
{
    double min =  100000.0;
    for(auto player :world.players)
    {
        double temp = distToMyTail(player.second.position[0],player.second.position[1], world);
        if(temp<min)
            min = temp;
    }
    return min;
}


inline bool isPlayerNearest(string playerIndex, GameWorld world){
    double min =  100000.0;
    string tempPlayer = "i";
    for(auto player :world.players)
    {
        double temp = distToPoint(player.second.position[0],player.second.position[1],world.me.position[0],  world.me.position[1]);
        if(temp<min)
        {
            tempPlayer = player.first;
            min = temp;
        }
    }
    return playerIndex==tempPlayer;
}

inline double SGauss(vector<vector<int>> points)
{
    if (points.size()==0) return 0;
    double result=0.0;
    for(int i=0; i<points.size()-1;i++)
    {
        result+=(points[i][0]*points[i+1][1]-points[i+1][0]*points[i][1]);

    }
    return abs(result/2)/30;
}


inline bool EnemyOnMyTerritory(GameWorld world)
{

    for(auto player: world.players)
    {
      if(isPointOnTerritory(player.second.position[0], player.second.position[1], world.me, world))
      {
          return true;
      }
    }
    return false;
}

inline bool IsPlayerTailOnMyTerritory(Player player , GameWorld world)
{
    for (auto line : player.lines)
    {
        if(isPointOnTerritory(line[0], line[1], world.me, world))
        {
            return true;
        }
    }
    return false;
}


inline bool EnemyTailOnMyTerritory(GameWorld world)
{

    for(auto player: world.players)
    {
        for (auto line : player.second.lines)
        {
            if(isPointOnTerritory(line[0], line[1], world.me, world))
            {
                return true;
            }
        }
    }
    return false;
}




inline vector<int> findNearestNotTerritoryCell(int next_x, int next_y,const GameWorld world)
{
    int i = 1;

    while (i<10)
    {
        for(int k=-i;k<=i;k++)
        {
            bool b1 = !isPointOnTerritory(next_x+world.width*k, next_y+world.width*i, world.me, world);
            bool b2 = !isPointOnTerritory(next_x+world.width*k, next_y-world.width*i, world.me, world);
            if(next_x+world.width*k<=world.width*(world.x_cells_count-1)-15
                    && next_x+world.width*k>15
                    && next_y+world.width*i<world.width*(world.y_cells_count-1) && next_y+world.width*i>15
                    && next_y-world.width*i<world.width*(world.y_cells_count-1) && next_y-world.width*i>15)
            {
                if(b1)
                {
                    return {next_x+world.width*k, next_y+world.width*i};
                }
                if(b2)
                {
                    return {next_x+world.width*k, next_y-world.width*i};
                }
            }
            for(int l=-i+1; l<i;l++)
            {
                bool bb1 = !isPointOnTerritory(next_x+world.width*i, next_y+world.width*l, world.me, world);
                bool bb2 = !isPointOnTerritory(next_x-world.width*i, next_y+world.width*l, world.me, world);
                if(next_y+world.width*l<=world.width*(world.y_cells_count-1)-15
                        && next_y+world.width*l>15
                        && next_x+world.width*i<=world.width*(world.x_cells_count-1)-15 && next_x+world.width*i>15
                        && next_x-world.width*i<=world.width*(world.x_cells_count-1)-15 && next_x-world.width*i>15)
                {
                    if(bb1)
                    {
                        return {next_x+world.width*i, next_y+world.width*l};
                    }
                    if(bb2)
                    {
                        return {next_x-world.width*i, next_y+world.width*l};
                    }
                }
            }

        }
        i++;

    }
    return {0,0};
}
