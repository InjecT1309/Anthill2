#ifndef MAP2D_H
#define MAP2D_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <vector>

#include "Point2D.h"
#include "Anthill.h"
#include "BlackAnthill.h"
#include "RedAnthill.h"
#include "Ant.h"
#include "BlackWorkerAnt.h"
#include "BlackSoldierAnt.h"
#include "RedAnt.h"

using std::cout;
using std::endl;
using std::vector;
using std::setw;

class Map2D
{
    public:
        Map2D(int width, int heigth);
        virtual ~Map2D();

        void mainLoop();
        void oneLoop();
        Point2D*** getPointMap();

    protected:

    private:
        const int m_width, m_height;
        int m_how_much_food, m_how_much_obstacle;
        int m_loop_iter;
        Point2D*** m_map;

        Anthill* m_black_anthill_ptr;
        Anthill* m_red_anthill_ptr;

        vector<Ant*> m_ant;

        void m_startMenu();
        void m_display();
        void m_displayHealth();
        void m_displayScent();
        char m_whatIsHere(int x, int y);
        void m_displayObjectCount();
        void m_displayWhatAntsSee();

        void m_generateMap();
        void m_placeObstacles();
        void m_placeFood();
        void m_placeAnthills();
        void m_placeFoodPatch(Point2D* point, int probability = 100);
        Point2D m_getRandomEmpty();

        void m_anthillSpawnsAnts(Anthill* anthill_ptr);
        void m_registerNewAnts(vector<Ant*> &ant);
        void m_antsWork();
        void m_pickUpAnt(Ant* ant);
        void m_placeAnt(Ant* ant);

        void m_clean_up();

        vector<Point2D*> m_getEmptyAroundAnthill(Anthill* anthill_ptr);
        vector<Point2D*> m_getVisibleForAnt(Ant* ant);
};

#endif // MAP2D_H
