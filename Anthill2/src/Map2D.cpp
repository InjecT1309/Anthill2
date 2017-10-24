#include "Map2D.h"

Map2D::Map2D(int width, int heigth) : m_width(width), m_height(heigth), m_loop_iter(0)
{
    srand(time(NULL));

    m_how_much_food = m_width*m_height/100;
    m_how_much_obstacle = m_width*m_height/25;

    m_map = new Point2D** [m_width];
    for(int x=0; x<m_width; x++)
    {
        m_map[x] = new Point2D* [m_height];
        for(int y=0; y<m_height; y++)
        {
            m_map[x][y] = new Point2D(x, y);
        }
    }

    m_generateMap();

//    m_startMenu();
}

void Map2D::mainLoop()
{
    while(true)
    {
        oneLoop();

        m_displayScent();

//        m_displayObjectCount();

        system("cls");
    }
}
void Map2D::oneLoop()
{
    if(m_loop_iter == 100)
    {
        Point2D tmp = m_getRandomEmpty();
        m_placeFoodPatch(&tmp);
        m_loop_iter = 0;
    }

    m_antsWork();

    m_black_anthill_ptr->lowerSpawnCountdown();
    m_red_anthill_ptr->lowerSpawnCountdown();

    if(m_black_anthill_ptr->doesAntSpawn()==true)   m_anthillSpawnsAnts(m_black_anthill_ptr);
    if(m_red_anthill_ptr->doesAntSpawn()==true)     m_anthillSpawnsAnts(m_red_anthill_ptr);

    m_clean_up();

    m_loop_iter++;
}
Point2D*** Map2D::getPointMap()
{
    return m_map;
}

void Map2D::m_startMenu()
{
    cout << "O - obstacle\n";
    cout << "F - food\n";
    cout << "B - black anthill\n";
    cout << "R - red anthill\n";
    cout << "W - black worker ant\n";
    cout << "S - black solider ant\n";
    cout << "A - red ant\n";
    cout << "press any key to start\n";

    getwchar();

    system("cls");
}

void Map2D::m_display()
{
    for(int y=0; y<m_height; y++)
    {
        for(int x=0; x<m_width; x++)
        {
            cout << setw(2) << m_whatIsHere(x, y);
        }
        cout << "|" << endl;
    }

    for(int x=0; x<m_width; x++)
    {
        cout << setw(2) << "-";
    }
    cout << endl;
}
void Map2D::m_displayHealth()
{
    for(int y=0; y<m_height; y++)
    {
        for(int x=0; x<m_width; x++)
        {
            if((m_map[x][y]->getFill()==blackWorkerAnt)||
               (m_map[x][y]->getFill()==blackSoliderAnt)||
               (m_map[x][y]->getFill()==redAnt))
            {
                cout << setw(3) << static_cast<Ant*>(m_map[x][y])->getHealth();
            }
            else    cout << setw(3) << m_whatIsHere(x, y);
        }
        cout << "|" << endl;
    }

    for(int x=0; x<m_width; x++)
    {
        cout << setw(3) << "-";
    }

    cout << endl;
}
void Map2D::m_displayScent()
{
    for(int y=0; y<m_height; y++)
    {
        for(int x=0; x<m_width; x++)
        {
            if(m_map[x][y]->getScentLevel()!=0)
            {
                if(m_map[x][y]->getFill()==empty)
                {
                    if(m_map[x][y]->getScentLevel()>0) cout << setw(2) << ".";
                    else    cout << setw(2) << " ";
                }
                else    cout << setw(2) << m_whatIsHere(x, y);
            }
            else    cout << setw(2) << m_whatIsHere(x, y);
        }
        cout << "|" << endl;
    }

    for(int x=0; x<m_width; x++)
    {
        cout << setw(2) << "-";
    }

    cout << endl;
}
char Map2D::m_whatIsHere(int x, int y)
{
    if(m_map[x][y]->getFill()==empty)           return ' ';
    if(m_map[x][y]->getFill()==obstacle)        return 'O';
    if(m_map[x][y]->getFill()==food)            return 'F';
    if(m_map[x][y]->getFill()==blackAnthill)    return 'B';
    if(m_map[x][y]->getFill()==redAnthill)      return 'R';
    if(m_map[x][y]->getFill()==blackWorkerAnt)  return 'W';
    if(m_map[x][y]->getFill()==blackSoliderAnt) return 'S';
    if(m_map[x][y]->getFill()==redAnt)          return 'A';
}
void Map2D::m_displayObjectCount()
{
    cout << "Points: "      << Point2D::obj_counter_point << endl;
    cout << "Anthills: "    << Anthill::obj_counter_anthill << endl;
    cout << "Ants: "        << Ant::obj_counter_ant << endl;
    cout << "Black worker ants: "   << BlackWorkerAnt::obj_counter_worker << endl;
    cout << "Black soldier ants: "  << BlackSoldierAnt::obj_counter_soldier << endl;
    cout << "Red ants: "    << RedAnt::obj_counter_red << endl;
}

void Map2D::m_generateMap()
{
    m_placeAnthills();
    m_placeObstacles();
    m_placeFood();
}
void Map2D::m_placeObstacles()
{
    Point2D empty_point;
    int x, y;

    for(int i=0; i<m_how_much_obstacle; i++)
    {
        do
        {
            empty_point = m_getRandomEmpty();
        }   while((empty_point.getDistance(m_black_anthill_ptr)<=1)||
                (empty_point.getDistance(m_red_anthill_ptr)<=1));

        x = empty_point.getX();
        y = empty_point.getY();
        delete m_map[x][y];
        m_map[x][y] = new Point2D(x, y, obstacle);
    }
}
void Map2D::m_placeFood()
{
    Point2D empty_point;
    int x, y;

    for(int i=0; i<m_how_much_food; i++)
    {
        do
        {
            empty_point = m_getRandomEmpty();
        }   while((empty_point.getDistance(m_black_anthill_ptr)<=2)||
                (empty_point.getDistance(m_red_anthill_ptr)<=2));

        m_placeFoodPatch(&empty_point);
    }
}
void Map2D::m_placeAnthills()
{
    Point2D empty_point;
    int x, y;

    do
    {
        empty_point = m_getRandomEmpty();
    }   while((empty_point.getX()==0)&&(empty_point.getX()==m_width-1)&&
              (empty_point.getY()==0)&&(empty_point.getY()==m_height-1));
    x = empty_point.getX();
    y = empty_point.getY();

    delete m_map[x][y];
    m_map[x][y] = new BlackAnthill(x, y);
    m_black_anthill_ptr = static_cast<Anthill*>(m_map[x][y]);

    do
    {
        empty_point = m_getRandomEmpty();
    }   while((empty_point.getX()==0)&&(empty_point.getX()==m_width)&&
              (empty_point.getY()==0)&&(empty_point.getY()==m_height));
    x = empty_point.getX();
    y = empty_point.getY();

    delete m_map[x][y];
    m_map[x][y] = new RedAnthill(x, y);
    m_red_anthill_ptr = static_cast<Anthill*>(m_map[x][y]);
}
void Map2D::m_placeFoodPatch(Point2D* point, int probability)
{
    int is_food_placed = rand()%100;

    if(is_food_placed<probability)
    {
        point->setFill(food);

        for(int x=0; x<m_width; x++)
        {
            for(int y=0; y<m_height; y++)
            {
                if((point->getDistance(m_map[x][y])==1)&&
                   (m_map[x][y]->getFill()==empty))
                    m_placeFoodPatch(m_map[x][y], probability-25);
            }
        }
    }
}
Point2D Map2D::m_getRandomEmpty()
{
    int x, y;

    do
    {
        x = rand()%m_width;
        y = rand()%m_height;
    }   while(m_map[x][y]->getFill()!=empty);

    return Point2D(x, y);
}

void Map2D::m_anthillSpawnsAnts(Anthill* anthill_ptr)
{
    vector<Point2D*> empty_around = m_getEmptyAroundAnthill(anthill_ptr);
    vector<Ant*> new_ants = anthill_ptr->spawnAnts(empty_around);
    m_registerNewAnts(new_ants);
}

void Map2D::m_registerNewAnts(vector<Ant*> &ant)
{
    int x, y;

    for(int i=0; i<ant.size(); i++)
    {
        x = ant[i]->getX();
        y = ant[i]->getY();

        m_map[x][y] = static_cast<Point2D*>(ant[i]);
        m_ant.push_back(ant[i]);
    }
}
void Map2D::m_antsWork()
{
    for(int i=0; i<m_ant.size(); i++)
    {
        vector<Point2D*> visible = m_getVisibleForAnt(m_ant.at(i));
        m_ant.at(i)->setVisible(visible);
        m_pickUpAnt(m_ant.at(i));
        m_ant.at(i)->work();
        m_placeAnt(m_ant.at(i));
    }
}
void Map2D::m_pickUpAnt(Ant* ant)
{
    int x = ant->getX();
    int y = ant->getY();

    if(ant->getFill()==blackWorkerAnt)
    {
        m_map[x][y] = new Point2D(x, y, empty, 100);
    }   else
    {
        m_map[x][y] = new Point2D(x, y);
    }
}
void Map2D::m_placeAnt(Ant* ant)
{
    delete m_map[ant->getX()][ant->getY()];

    m_map[ant->getX()][ant->getY()] = static_cast<Point2D*> (ant);
}

void Map2D::m_clean_up()
{
    int x, y;
    Fill ant_fill;
    bool is_carrying_food;

    for(int i=0; i<m_ant.size(); i++)
    {
        if(m_ant[i]->checkIfDead()==true)
        {
            x = m_ant[i]->getX();
            y = m_ant[i]->getY();
            ant_fill = m_ant[i]->getFill();
            if(ant_fill==blackWorkerAnt)    is_carrying_food = static_cast<BlackWorkerAnt*>(m_ant[i])->getIsCarryingFood();

            m_ant.erase(m_ant.begin()+i);
            i--;

            delete m_map[x][y];

            if((ant_fill==blackWorkerAnt)&&(is_carrying_food==true))
            {
                m_map[x][y]->setFill(food);
            }
            else
            {
                m_map[x][y] = new Point2D(x, y);
            }
        }
    }

    for(int x=0; x<m_width; x++)
    {
        for(int y=0; y<m_height; y++)
        {
            m_map[x][y]->lowerScentLevel();
        }
    }
}

vector<Point2D*> Map2D::m_getEmptyAroundAnthill(Anthill* anthill_ptr)
{
    vector<Point2D*> empty_around;

    for(int x=0; x<m_width; x++)
    {
        for(int y=0; y<m_height; y++)
        {
            if((anthill_ptr->getDistance(m_map[x][y])==1)&&(m_map[x][y]->getFill()==empty))
            {
                empty_around.push_back(m_map[x][y]);
            }
        }
    }

    return empty_around;
}
vector<Point2D*> Map2D::m_getVisibleForAnt(Ant* ant)
{
    vector<Point2D*> output;

    for(int x=0; x<m_width; x++)
    {
        for(int y=0; y<m_height; y++)
        {
            if(ant->getDistance(m_map[x][y])<=ant->getVision())
            {
                output.push_back(m_map[x][y]);
            }
        }
    }

    return output;
}

Map2D::~Map2D()
{
    BlackAnthill* delete_me_black_anthill;
    RedAnthill* delete_me_red_anthill;
    BlackWorkerAnt* delete_me_worker;
    BlackSoldierAnt* delete_me_soldier;
    RedAnt* delete_me_red;

    for(int x=0; x<m_width; x++)
    {
        for(int y=0; y<m_height; y++)
        {
            if(m_map[x][y]->getFill()==blackAnthill)
            {
                delete_me_black_anthill = static_cast<BlackAnthill*>(m_map[x][y]);
                delete delete_me_black_anthill;
            }   else
            if(m_map[x][y]->getFill()==redAnthill)
            {
                delete_me_red_anthill = static_cast<RedAnthill*>(m_map[x][y]);
                delete delete_me_red_anthill;
            }   else
            if(m_map[x][y]->getFill()==blackWorkerAnt)
            {
                delete_me_worker = static_cast<BlackWorkerAnt*>(m_map[x][y]);
                delete delete_me_worker;
            }   else
            if(m_map[x][y]->getFill()==blackSoliderAnt)
            {
                delete_me_soldier = static_cast<BlackSoldierAnt*>(m_map[x][y]);
                delete delete_me_soldier;
            }   else
            if(m_map[x][y]->getFill()==redAnt)
            {
                delete_me_red = static_cast<RedAnt*>(m_map[x][y]);
                delete delete_me_red;
            }
            else
                delete m_map[x][y];
        }
        delete m_map[x];
    }
    delete m_map;
}
