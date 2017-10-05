#include <iostream>

#include "Map2D.h"

using namespace std;

int main()
{
    Map2D* Map = new Map2D(40, 20);
    Map->mainLoop();
    delete Map;

    return 0;
}
