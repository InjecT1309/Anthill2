#ifndef ANT_H
#define ANT_H

#include <vector>
#include <stdlib.h>

#include "Point2D.h"
#include "Fill.h"

using std::vector;

class Ant : public Point2D
{
    public:
        Ant(int x, int y, Fill ant_type);
        virtual ~Ant();

        static int obj_counter_ant; //debug

        void setVisible(vector<Point2D*> whats_around);
        virtual void work() = 0;
        bool checkIfDead();

        int getVision();
        int getHealth();
        int howManyVisible();

    protected:
        vector<Point2D*> m_visible;
        vector<Point2D*> m_adjacent;

        int m_health_points;
        int m_agression;
        int m_vision_radious;
        bool m_is_dead;

        void m_setAdjacent();
        bool m_checkIfFillIsVisible(Fill fill);
        bool m_checkIfFillIsAdjacent(Fill fill);
        Point2D* m_findClosestFill(Fill fill);
        Point2D* m_pickNewPosition();
        Point2D* m_pickNewPosition(Point2D* destination);
        bool m_anyMovementAvailable();

        Ant* m_whichAntToAttack(Fill ant_type);
        void m_attack(Ant* enemy);
        void m_takeDamage(int how_much_dmg);
};

#endif // ANT_H
