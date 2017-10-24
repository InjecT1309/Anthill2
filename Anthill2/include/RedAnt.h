#ifndef REDANT_H
#define REDANT_H

#include "Point2D.h"
#include "Ant.h"
#include "BlackWorkerAnt.h"
#include "Fill.h"

class RedAnt : public Ant
{
    public:
        RedAnt(int x, int y);
        virtual ~RedAnt();

        static int obj_counter_red;

        void work() override;

    protected:

    private:
        int m_hunger_value;

        void m_lowerHealth();
        Point2D* m_whichFoodToEat();
        void m_eatFood(Point2D* food);
        bool m_checkIfNearbyAntHasFood();
        Point2D* m_findClosestAntWithFood();
};

#endif // REDANT_H
