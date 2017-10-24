#ifndef BLACKANTHILL_H
#define BLACKANTHILL_H

#include <vector>
#include <stdlib.h>

#include "Point2D.h"
#include "Anthill.h"
#include "Ant.h"
#include "BlackWorkerAnt.h"
#include "BlackSoldierAnt.h"

using std::vector;

class BlackAnthill : public Anthill
{
    public:
        BlackAnthill(int x, int y);
        virtual ~BlackAnthill();

        vector<Ant*> spawnAnts(vector<Point2D*> &empty_around) override;

    protected:

    private:
};

#endif // BLACKANTHILL_H
