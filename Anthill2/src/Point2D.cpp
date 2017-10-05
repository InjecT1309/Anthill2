#include "Point2D.h"

int Point2D::obj_counter_point = 0;

Point2D::Point2D()
{
    obj_counter_point++;
}
Point2D::Point2D(int x, int y, Fill fill, int scent_level)
                : m_x(x), m_y(y), m_fill(fill), m_scent_level(scent_level)
{
    obj_counter_point++;
}

int Point2D::getX()
{
    return m_x;
}
int Point2D::getY()
{
    return m_y;
}
Fill Point2D::getFill()
{
    return m_fill;
}
int Point2D::getScentLevel()
{
    return m_scent_level;
}
void Point2D::lowerScentLevel()
{
    if(m_scent_level>0) m_scent_level-=4;
}
int Point2D::getDistance(Point2D* point)
{
    return sqrt(pow((m_x-point->m_x), 2) + pow((m_y-point->m_y), 2));
}

Point2D::~Point2D()
{
    obj_counter_point--;
}
