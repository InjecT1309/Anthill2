#include "BlackWorkerAnt.h"

int BlackWorkerAnt::obj_counter_worker = 0;

BlackWorkerAnt::BlackWorkerAnt(int x, int y, Point2D* anthill_pos) : Ant(x, y, blackWorkerAnt),
                                        m_anthill_pos(anthill_pos), m_energy(100), m_is_carrying_food(false)
{
    m_agression=rand()%10;
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
        Ant::m_pickNewPosition(m_anthill_pos);
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
Point2D* BlackWorkerAnt::m_whichFoodToPick()
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
void BlackWorkerAnt::m_pickUpFood(Point2D* food)
{
    m_food_carried = food;
    food->setFill(empty);
    m_is_carrying_food = true;
}
void BlackWorkerAnt::m_deliverFood()
{
    m_is_carrying_food = false;
}
Point2D* BlackWorkerAnt::m_findStrongestScent()
{
    Point2D tmp = Point2D(0, 0, empty, 0);
    Point2D* strongest;
    Point2D* checked;

    for(int i=0; i<m_adjacent.size(); i++)
    {
        if((m_adjacent[i]->getFill()==empty)&&
           (m_adjacent[i]->getX()!=m_prev_pos_x)&&(m_adjacent[i]->getY()!=m_prev_pos_y))
        {
            checked = m_adjacent[i];

            if((checked->getScentLevel())>(strongest->getScentLevel()))
            {
                strongest = checked;
            }
        }
    }

    if(strongest->getScentLevel()==0)  return m_pickNewPosition();

    return strongest;
}

BlackWorkerAnt::~BlackWorkerAnt()
{
    obj_counter_worker--;
}
