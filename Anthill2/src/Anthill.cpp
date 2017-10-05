#include "Anthill.h"

int Anthill::obj_counter_anthill = 0;

Anthill::Anthill(int x, int y, Fill anthill_color) : Point2D(x, y, anthill_color), m_spawn_countdown(2)
{

}

bool Anthill::doesAntSpawn()
{
    m_spawn_countdown--;

    if(m_spawn_countdown == 0)
    {
        if(m_fill==blackAnthill)    m_spawn_countdown=20;
        if(m_fill==redAnthill)      m_spawn_countdown=20;
        return true;
    }   else
        return false;
}
vector<Ant*> Anthill::spawnAnts(vector<Point2D*> &empty_around)
{
    vector<Ant*> ant_vector;
    int x, y;

    if(m_fill==blackAnthill)
    {
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
    }
    if(m_fill==redAnthill)
    {
        bool does_ant_spawn;

        for(int i=0; i<empty_around.size(); i++)
        {
            does_ant_spawn=rand()%3;
            if(does_ant_spawn==true)
            {
                x = empty_around[i]->getX();
                y = empty_around[i]->getY();

                delete empty_around[i];

                empty_around[i] = new RedAnt(x, y);

                ant_vector.push_back(static_cast<Ant*>(empty_around[i]));
            }
        }

    }

    return ant_vector;
}

Anthill::~Anthill()
{
    //dtor
}
