#ifndef BLACKSOLDIERANT_H
#define BLACKSOLDIERANT_H

#include "Point2D.h"
#include "Ant.h"
#include "Fill.h"

class BlackSoldierAnt : public Ant
{
    public:
        BlackSoldierAnt(int x, int y, Point2D* anthill_pos);
        virtual ~BlackSoldierAnt();

        static int obj_counter_soldier;

        void work() override;

    protected:

    private:
        Point2D* m_anthill_pos;
};

#endif // BLACKSOLDIERANT_H
