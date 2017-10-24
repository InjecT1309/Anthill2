#include "BlackAnthill.h"

BlackAnthill::BlackAnthill(int x, int y) : Anthill(x, y)
{
    m_fill = blackAnthill;
}

vector<Ant*> BlackAnthill::spawnAnts(vector<Point2D*> &empty_around)
{
    vector<Ant*> ant_vector;
    int x, y;

    int does_ant_spawn;
    int is_a_worker;

    for(int i=0; i<empty_around.size(); i++)
    {
        does_ant_spawn=rand()%2;
        if(does_ant_spawn==0)
        {
            x = empty_around[i]->getX();
            y = empty_around[i]->getY();

            delete empty_around[i];

            is_a_worker=rand()%2;

            if(is_a_worker!=0)
            {
                empty_around[i] = new BlackWorkerAnt(x, y, static_cast<Point2D*>(this));
            }
            else
            {
                empty_around[i] = new BlackSoldierAnt(x, y, static_cast<Point2D*>(this));
            }

            ant_vector.push_back(static_cast<Ant*>(empty_around[i]));
        }
    }

    return ant_vector;
}

BlackAnthill::~BlackAnthill()
{
    //dtor
}
