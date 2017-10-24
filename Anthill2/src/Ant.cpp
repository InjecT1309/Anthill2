#include "Ant.h"

int Ant::obj_counter_ant = 0; //debug

Ant::Ant(int x, int y, Fill ant_type) : Point2D(x, y, ant_type), m_health_points(100), m_agression(1),
            m_vision_radious(7), m_prev_pos_x(-1), m_prev_pos_y(-1)
{
    obj_counter_ant++;
}

void Ant::setVisible(vector<Point2D*> whats_around)
{
    m_visible.clear();
    m_visible=whats_around;

    m_setAdjacent();
}

bool Ant::checkIfDead()
{
    if(m_health_points<=0)
        return true;
    else
        return false;
}
int Ant::getVision()
{
    return m_vision_radious;
}
int Ant::getHealth()
{
    return m_health_points;
}

void Ant::m_setAdjacent()
{
    m_adjacent.clear();

    for(int i=0; i<m_visible.size(); i++)
    {
        if(this->getDistance(m_visible[i])==1) m_adjacent.push_back(m_visible[i]);
    }
}
bool Ant::m_checkIfFillIsVisible(Fill fill)
{
    for(int i=0; i<m_visible.size(); i++)
    {
        if(m_visible[i]->getFill()==fill)   return true;
    }

    return false;
}
bool Ant::m_checkIfFillIsAdjacent(Fill fill)
{
    for(int i=0; i<m_adjacent.size(); i++)
    {
        if(m_adjacent[i]->getFill()==fill)   return true;
    }

    return false;
}
Point2D* Ant::m_findClosestFill(Fill fill)
{
    Point2D* closest = m_visible[0];

    for(int i=0; i<m_visible.size(); i++)
    {
        if((m_visible[i]->getFill()==fill)&&
           (getDistance(m_visible[i])<getDistance(closest)))
           {
                closest = m_visible[i];
           }
    }

    return closest;
}
Point2D* Ant::m_pickNewPosition(bool continue_move_direction)
{
    if(continue_move_direction==true)
    {
        int is_continuing = rand()%4;
        if(is_continuing<3)
        {
            Point2D* continue_point = m_set_continue_point();
            if(continue_point->getFill() == empty)
            {
                m_move(continue_point);
                return continue_point;
            }
            else
            {
                continue_move_direction=false;
            }
        }
        else
        {
            continue_move_direction=false;
        }
    }
    if(continue_move_direction==false)
    {
        if(m_anyMovementAvailable()==true)
        {
            int which_direction;

            do
            {
                which_direction = rand()%m_adjacent.size();
            }   while(m_adjacent[which_direction]->getFill()!=empty);

            m_move(m_adjacent[which_direction]);

            return m_adjacent[which_direction];
        }

        return static_cast<Point2D*>(this);
    }
}
Point2D* Ant::m_pickNewPosition(Point2D* destination)
{
    if(m_anyMovementAvailable()==true)
    {
        Point2D* point_to_move;

        //gets a point to compare with later
        for(int i=0; i<m_adjacent.size(); i++)
        {
            if(m_adjacent[i]->getFill()==empty)
            {
                point_to_move = m_adjacent[i];
                break;
            }
        }

        for(int i=0; i<m_adjacent.size(); i++)
        {
            if((m_adjacent[i]->getFill()==empty)&&
                (m_adjacent[i]->getDistance(destination)<=point_to_move->getDistance(destination)))
                point_to_move = m_adjacent[i];
        }

        m_move(point_to_move);

        return point_to_move;
    }
    return static_cast<Point2D*>(this);
}
void Ant::m_move(Point2D* point_to_move)
{
    m_prev_pos_x = m_x;
    m_prev_pos_y = m_y;

    m_x = point_to_move->getX();
    m_y = point_to_move->getY();
}
Point2D* Ant::m_set_continue_point()
{
    if(m_prev_pos_x!=-1)
    {
        int diff_x = m_x - m_prev_pos_x;
        int diff_y = m_y - m_prev_pos_y;

        for(int i=0; i<m_visible.size(); i++)
        {
            if((m_visible[i]->getX() == m_x+diff_x)&&(m_visible[i]->getY() == m_y+diff_y))
            {
                return m_visible[i];
            }
        }
    }
    return m_adjacent[0];
}
bool Ant::m_anyMovementAvailable()
{
    for(int i=0; i<m_adjacent.size(); i++)
    {
        if(m_adjacent[i]->getFill()==empty) return true;
    }
    return false;
}
Ant* Ant::m_whichAntToAttack(Fill ant_type)
{
    Ant* output;

    for(int i=0; i<m_adjacent.size(); i++)
    {
        if(m_adjacent[i]->getFill()==ant_type)
        {
            output = static_cast<Ant*>(m_adjacent[i]);
            break;
        }
    }

    return output;
}
void Ant::m_attack(Ant* enemy)
{
    if(m_agression>0)
        enemy->m_takeDamage(m_agression);
    else
        m_pickNewPosition();
}
void Ant::m_takeDamage(int how_much_dmg)
{
    m_health_points-=how_much_dmg;
}

Ant::~Ant()
{
    obj_counter_ant--;
}
