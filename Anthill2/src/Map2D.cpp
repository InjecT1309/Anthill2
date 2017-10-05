#include "Map2D.h"

Map2D::Map2D(int width, int heigth) : m_width(width), m_height(heigth)
{
    srand(time(NULL));

    m_how_much_food = m_width*m_height/20;
    m_how_much_obstacle = m_width*m_height/15;

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
}

void Map2D::mainLoop()
{
    while(true)
    {
        m_display();

        m_antsWork();

        if(m_black_anthill_ptr->doesAntSpawn()==true)   m_anthillSpawnsAnts(m_black_anthill_ptr);
        if(m_red_anthill_ptr->doesAntSpawn()==true)     m_anthillSpawnsAnts(m_red_anthill_ptr);

        Food::lowerFoodDropCountdown();
        if(Food::food_drop_countown==0)
        {
            Food::food_drop_countown=500;
            m_placeFood();
        }

        m_clean_up();

//        m_displayFood();
//        m_displayHealth();

//        m_displayObjectCount();
//        m_displayWhatAntsSee();

//        getwchar();

        system("cls");
    }
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
void Map2D::m_displayFood()
{
    for(int x=0; x<m_width; x++)
    {
        for(int y=0; y<m_height; y++)
        {
            if(m_map[x][y]->getFill()==food)    cout << setw(3) << static_cast<Food*>(m_map[x][y])->getFoodLevel();
            else                                cout << setw(3) << m_whatIsHere(x, y);
        }
        cout << "|" << endl;
    }

    for(int x=0; x<m_width; x++)
    {
        cout << setw(3) << "-";
    }

    cout << endl;
}
void Map2D::m_displayHealth()
{
    for(int x=0; x<m_width; x++)
    {
        for(int y=0; y<m_height; y++)
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
    cout << "Food: "        << Food::obj_counter_food << endl;
    cout << "Anthills: "    << Anthill::obj_counter_anthill << endl;
    cout << "Ants: "        << Ant::obj_counter_ant << endl;
    cout << "Black worker ants: "   << BlackWorkerAnt::obj_counter_worker << endl;
    cout << "Black soldier ants: "  << BlackSoldierAnt::obj_counter_soldier << endl;
    cout << "Red ants: "    << RedAnt::obj_counter_red << endl;
}
void Map2D::m_displayWhatAntsSee()
{
    for(int i=0; i<m_ant.size(); i++)
    {
        cout << "Ant nr: " << i << " sees " << m_ant[i]->howManyVisible() << " points\n";
    }
}

void Map2D::m_generateMap()
{
    m_placeObstacle();
    m_placeFood();
    m_placeAnthills();
}
void Map2D::m_placeObstacle()
{
    Point2D empty_point;
    int x, y;

    for(int i=0; i<m_how_much_obstacle; i++)
    {
        empty_point = m_getRandomEmpty();
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
        empty_point = m_getRandomEmpty();
        x = empty_point.getX();
        y = empty_point.getY();
        delete m_map[x][y];
        m_map[x][y] = new Food(x, y);
    }
}
void Map2D::m_placeAnthills()
{
    Point2D empty_point;
    int x, y;

    empty_point = m_getRandomEmpty();
    x = empty_point.getX();
    y = empty_point.getY();

    delete m_map[x][y];
    m_map[x][y] = new Anthill(x, y, blackAnthill);
    m_black_anthill_ptr = static_cast<Anthill*>(m_map[x][y]);

    empty_point = m_getRandomEmpty();
    x = empty_point.getX();
    y = empty_point.getY();

    delete m_map[x][y];
    m_map[x][y] = new Anthill(x, y, redAnthill);
    m_red_anthill_ptr = static_cast<Anthill*>(m_map[x][y]);
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
                m_map[x][y] = new Food(x, y, 10);
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

            if(m_map[x][y]->getFill()==food)
            {
                if(static_cast<Food*>(m_map[x][y])->checkIfEmpty()==true)
                {
                    delete m_map[x][y];
                    m_map[x][y] = new Point2D(x, y);
                }
            }
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
    Food* delete_me_food;
    Anthill* delete_me_anthill;
    BlackWorkerAnt* delete_me_worker;
    BlackSoldierAnt* delete_me_soldier;
    RedAnt* delete_me_red;

    for(int x=0; x<m_width; x++)
    {
        for(int y=0; y<m_height; y++)
        {
            if(m_map[x][y]->getFill()==food)
            {
                delete_me_food = static_cast<Food*>(m_map[x][y]);
                delete delete_me_food;
            }   else
            if((m_map[x][y]->getFill()==redAnthill)||(m_map[x][y]->getFill()==blackAnthill))
            {
                delete_me_anthill = static_cast<Anthill*>(m_map[x][y]);
                delete delete_me_anthill;
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
