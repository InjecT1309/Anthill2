#include "BlackSoldierAnt.h"

int BlackSoldierAnt::obj_counter_soldier = 0;

BlackSoldierAnt::BlackSoldierAnt(int x, int y, Point2D* anthill_pos) : Ant(x, y, blackSoliderAnt), m_anthill_pos(anthill_pos)
{
    m_agression = 10+rand()%40;
    obj_counter_soldier++;
}

void BlackSoldierAnt::work()
{
    if(m_checkIfFillIsAdjacent(redAnt))
    {
        m_attack(m_whichAntToAttack(redAnt));
    }
    else if(m_checkIfFillIsVisible(redAnt))
    {
        m_pickNewPosition(m_findClosestFill(redAnt));
    }
    else if(getDistance(m_anthill_pos)>6)
    {
        m_pickNewPosition(m_anthill_pos);
    }
    else
    {
        m_pickNewPosition(false);
    }
}

BlackSoldierAnt::~BlackSoldierAnt()
{
    obj_counter_soldier--;
}
