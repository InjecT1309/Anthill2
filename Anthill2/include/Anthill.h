#ifndef ANTHILL_H
#define ANTHILL_H

#include <vector>
#include <stdlib.h>

#include "Point2D.h"
#include "Ant.h"
#include "BlackWorkerAnt.h"
#include "BlackSoldierAnt.h"
#include "RedAnt.h"

using std::vector;

class Anthill : public Point2D
{
    public:
        Anthill(int x, int y);
        virtual ~Anthill();

        static int obj_counter_anthill;

        void lowerSpawnCountdown();
        bool doesAntSpawn();
        virtual vector<Ant*> spawnAnts(vector<Point2D*> &empty_around) = 0;

    protected:

    private:
        int m_spawn_countdown;
};

#endif // ANTHILL_H
