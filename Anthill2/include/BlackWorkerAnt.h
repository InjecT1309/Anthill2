#ifndef BLACKWORKERANT_H
#define BLACKWORKERANT_H

#include "Point2D.h"
#include "Food.h"
#include "Ant.h"
#include "Fill.h"

class BlackWorkerAnt : public Ant
{
    public:
        BlackWorkerAnt(int x, int y, Point2D* anthill_pos);
        virtual ~BlackWorkerAnt();

        static int obj_counter_worker;

        void work() override;
        bool getIsCarryingFood();

    protected:

    private:
        int m_energy;
        bool m_is_resting;
        bool m_is_carrying_food;
        Point2D* m_anthill_pos;

        void m_rest();
        void m_getTired();
        Food* m_whichFoodToPick();
        void m_pickUpFood(Food* food);
        void m_deliverFood();
        Point2D* m_findStrongestScent();
};

#endif // BLACKWORKERANT_H
