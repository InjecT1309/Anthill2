#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>

#include "Fill.h"

class Point2D
{
    public:
        Point2D();
        Point2D(int x, int y, Fill fill = empty, int scent_level=0);
        virtual ~Point2D();

        static int obj_counter_point; //debug

        int getX();
        int getY();
        Fill getFill();
        int getScentLevel();
        void lowerScentLevel();
        int getDistance(Point2D* point);

    protected:
        int m_x, m_y;
        int m_scent_level;
        Fill m_fill;

    private:
};

#endif // POINT2D_H
