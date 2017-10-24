#ifndef REDANTHILL_H
#define REDANTHILL_H

#include <vector>
#include <stdlib.h>

#include "Point2D.h"
#include "Anthill.h"
#include "Ant.h"
#include "RedAnt.h"

using std::vector;

class RedAnthill : public Anthill
{
    public:
        RedAnthill(int x, int y);
        virtual ~RedAnthill();

        vector<Ant*> spawnAnts(vector<Point2D*> &empty_around) override;

    protected:

    private:
};

#endif // REDANTHILL_H
