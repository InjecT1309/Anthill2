#include "Food.h"

int Food::obj_counter_food = 0;
int Food::food_drop_countown = 500;

Food::Food(int x, int y, int food_level) : Point2D(x, y, food), m_food_lvl(food_level), m_is_empty(false)
{
    obj_counter_food++;
}

void Food::lowerFoodDropCountdown()
{
    food_drop_countown--;
}

void Food::lowerFoodLevel(int how_much)
{
    if((m_food_lvl-=how_much)<=0)  m_is_empty = true;
}
int Food::getFoodLevel()
{
    return m_food_lvl;
}
bool Food::checkIfEmpty()
{
    return m_is_empty;
}

Food::~Food()
{
    obj_counter_food--;
}
