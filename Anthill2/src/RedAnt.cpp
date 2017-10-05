#include "RedAnt.h"

int RedAnt::obj_counter_red = 0;

RedAnt::RedAnt(int x, int y) : Ant(x, y, redAnt)
{
    m_agression = 15;

    obj_counter_red++;
}

void RedAnt::work()
{
    m_lowerHealth();

    if(m_checkIfFillIsAdjacent(blackSoliderAnt))
    {
        m_attack(m_whichAntToAttack(blackSoliderAnt));
    }
    else if(m_checkIfFillIsAdjacent(blackWorkerAnt))
    {
        m_attack(m_whichAntToAttack(blackWorkerAnt));
    }
    else if(m_health_points<120)
    {
        if(m_checkIfFillIsAdjacent(food)==true)
        {
            m_eatFood(m_whichFoodToEat());
        }
        else if(m_checkIfNearbyAntHasFood()==true)
        {
            m_pickNewPosition(m_findClosestAntWithFood());
        }
        else if(m_checkIfFillIsVisible(food)==true)
        {
            m_pickNewPosition(m_findClosestFill(food));
        }
        else
        {
            m_pickNewPosition();
        }
    }
    else
    {
        m_pickNewPosition();
    }
}

void RedAnt::m_lowerHealth()
{
    m_health_points--;
    if(m_health_points<=0)  m_is_dead=true;
}
Food* RedAnt::m_whichFoodToEat()
{
    Food* output;

    for(int i=0; i<m_adjacent.size(); i++)
    {
        if(m_adjacent[i]->getFill()==food)
        {
            output = static_cast<Food*>(m_adjacent[i]);
            break;
        }
    }

    return output;
}
void RedAnt::m_eatFood(Food* food)
{
    food->lowerFoodLevel(5);
    m_health_points+=10;
}
bool RedAnt::m_checkIfNearbyAntHasFood()
{
    for(int i=0; i<m_visible.size(); i++)
    {
        if(m_visible[i]->getFill()==blackWorkerAnt)
        {
            if(static_cast<BlackWorkerAnt*>(m_visible[i])->getIsCarryingFood()==true)
            {
                return true;
            }
        }
    }

    return false;
}
Point2D* RedAnt::m_findClosestAntWithFood()
{
    Point2D* closest = m_visible[0];

    for(int i=0; i<m_visible.size(); i++)
    {
        if((m_visible[i]->getFill()==blackWorkerAnt)&&
           (static_cast<BlackWorkerAnt*>(m_visible[i])->getIsCarryingFood()==true)&&
           (getDistance(m_visible[i])<getDistance(closest)))
           {
                closest = m_visible[i];
           }
    }

    return closest;
}

RedAnt::~RedAnt()
{
    obj_counter_red--;
}
