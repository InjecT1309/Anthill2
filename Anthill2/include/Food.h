#ifndef FOOD_H
#define FOOD_H

#include "Point2D.h"
#include "Fill.h"

#include <iostream>
using namespace std;

class Food : public Point2D
{
    public:
        Food(int x, int y, int food_level=100);
        virtual ~Food();

        static int obj_counter_food;
        static int food_drop_countown;

        static void lowerFoodDropCountdown();

        void lowerFoodLevel(int how_much);
        int getFoodLevel();
        bool checkIfEmpty();

    protected:

    private:
        int m_food_lvl;
        bool m_is_empty;
};

#endif // FOOD_H
