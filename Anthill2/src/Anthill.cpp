#include "Anthill.h"

int Anthill::obj_counter_anthill = 0;

Anthill::Anthill(int x, int y) : Point2D(x, y), m_spawn_countdown(1)
{
    obj_counter_anthill++;
}

void Anthill::lowerSpawnCountdown()
{
    if(m_spawn_countdown>0)
        m_spawn_countdown--;
}
bool Anthill::doesAntSpawn()
{
    if(m_spawn_countdown == 0)
    {
        m_spawn_countdown=20;
        return true;
    }
    else
        return false;
}

Anthill::~Anthill()
{
    obj_counter_anthill--;
}
