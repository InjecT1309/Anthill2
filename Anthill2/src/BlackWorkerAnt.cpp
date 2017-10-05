#include "BlackWorkerAnt.h"

int BlackWorkerAnt::obj_counter_worker = 0;

BlackWorkerAnt::BlackWorkerAnt(int x, int y, Point2D* anthill_pos) : Ant(x, y, blackWorkerAnt),
                                        m_anthill_pos(anthill_pos), m_energy(100), m_is_carrying_food(false)
{
    m_agression=5;
    obj_counter_worker++;
}

void BlackWorkerAnt::work()
{
    bool is_following_scent;

    if(m_is_resting==true)
    {
        m_rest();
    }
    else if(m_energy<=0)
    {
        m_is_resting = true;
    }
    else if(m_checkIfFillIsAdjacent(redAnt)==true)
    {
        m_attack(m_whichAntToAttack(redAnt));
        m_getTired();
    }
    else if((m_is_carrying_food==true)&&(getDistance(m_anthill_pos)==1))
    {
        m_deliverFood();
        m_getTired();
    }
    else if(m_is_carrying_food==true)
    {
        m_pickNewPosition(m_anthill_pos);
        m_getTired();
    }
    else if(m_checkIfFillIsAdjacent(food)==true)
    {
        m_pickUpFood(m_whichFoodToPick());
        m_getTired();
    }
    else if(m_checkIfFillIsVisible(food)==true)
    {
        m_pickNewPosition(m_findClosestFill(food));
        m_getTired();
    }
    else
    {
        is_following_scent = rand()%2;
        if(is_following_scent==true)
        {
            m_pickNewPosition(m_findStrongestScent());
            m_getTired();
        }
        else
        {
            m_pickNewPosition();
            m_getTired();
        }
    }
}
bool BlackWorkerAnt::getIsCarryingFood()
{
    return m_is_carrying_food;
}

void BlackWorkerAnt::m_rest()
{
    m_energy+=10;
    if(m_energy>=100)   m_is_resting=false;
}
void BlackWorkerAnt::m_getTired()
{
    m_energy-=2;
}
Food* BlackWorkerAnt::m_whichFoodToPick()
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
void BlackWorkerAnt::m_pickUpFood(Food* food)
{
    food->lowerFoodLevel(10);
    m_is_carrying_food = true;
}
void BlackWorkerAnt::m_deliverFood()
{
    m_is_carrying_food = false;
}
Point2D* BlackWorkerAnt::m_findStrongestScent()
{
    Point2D* strongest = m_visible[0];
    Point2D* checked;

    for(int i=0; i<m_visible.size(); i++)
    {
        if((m_visible[i]->getFill()==empty)&&(getDistance(m_visible[i])>3))
        {
            checked = m_visible[i];

            if((checked->getScentLevel())>(strongest->getScentLevel()))
            {
                strongest = checked;
            }
        }
    }

    return strongest;
}

BlackWorkerAnt::~BlackWorkerAnt()
{
    obj_counter_worker--;
}
