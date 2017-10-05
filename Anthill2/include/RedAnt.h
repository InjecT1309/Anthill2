#ifndef REDANT_H
#define REDANT_H

#include "Point2D.h"
#include "Food.h"
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
        void m_lowerHealth();
        Food* m_whichFoodToEat();
        void m_eatFood(Food* food);
//        bool m_checkIfAntHas
        bool m_checkIfNearbyAntHasFood();
        Point2D* m_findClosestAntWithFood();
};

#endif // REDANT_H
