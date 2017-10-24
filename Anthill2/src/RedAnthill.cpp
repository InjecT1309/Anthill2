#include "RedAnthill.h"

RedAnthill::RedAnthill(int x, int y) : Anthill(x, y)
{
    m_fill = redAnthill;
}

vector<Ant*> RedAnthill::spawnAnts(vector<Point2D*> &empty_around)
{
    vector<Ant*> ant_vector;
    int x, y;
    bool does_ant_spawn;

    for(int i=0; i<empty_around.size(); i++)
    {
        does_ant_spawn=rand()%2;
        if(does_ant_spawn==true)
        {
            x = empty_around[i]->getX();
            y = empty_around[i]->getY();

            delete empty_around[i];

            empty_around[i] = new RedAnt(x, y);

            ant_vector.push_back(static_cast<Ant*>(empty_around[i]));
        }
    }

    return ant_vector;
}

RedAnthill::~RedAnthill()
{
    //dtor
}
