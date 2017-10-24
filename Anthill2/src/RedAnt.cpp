#include "RedAnt.h"

int RedAnt::obj_counter_red = 0;

RedAnt::RedAnt(int x, int y) : Ant(x, y, redAnt), m_hunger_value(0)
{
    m_agression = rand()%40;

    obj_counter_red++;
}

void RedAnt::work()
{
    if(m_hunger_value>15)   m_lowerHealth();
    if(m_checkIfFillIsAdjacent(blackSoliderAnt))
    {
        m_attack(m_whichAntToAttack(blackSoliderAnt));
    }
    else if(m_checkIfFillIsAdjacent(blackWorkerAnt))
    {
        m_attack(m_whichAntToAttack(blackWorkerAnt));
    }
    else if(m_hunger_value>15)
    {
        if(m_checkIfNearbyAntHasFood()==true)
        {
            m_pickNewPosition(m_findClosestAntWithFood());
        }
        else if(m_checkIfFillIsAdjacent(food)==true)
        {
            m_eatFood(m_whichFoodToEat());
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

    m_hunger_value++;
}

void RedAnt::m_lowerHealth()
{
    m_health_points-=2;
}
Point2D* RedAnt::m_whichFoodToEat()
{
    Point2D* output;

    for(int i=0; i<m_adjacent.size(); i++)
    {
        if(m_adjacent[i]->getFill()==food)
        {
            output = m_adjacent[i];
            break;
        }
    }

    return output;
}
void RedAnt::m_eatFood(Point2D* food)
{
    food->setFill(empty);
    m_health_points+=15;
    m_hunger_value=0;
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
