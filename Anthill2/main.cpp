#include <SFML/Graphics.hpp>

#include "Map2D.h"
#include "Gui.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Anthill v1.1");

    Gui* gui = new Gui(window, 20, 15);
    Map2D* Map = new Map2D(20, 15);

    sf::Time tmp = sf::seconds(0.2f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Map->oneLoop();
        gui->setPanels(Map->getPointMap());

        window.clear(sf::Color(0, 153, 0));
        gui->display();
        window.display();

        sf::sleep(tmp);
    }

    delete gui;
    delete Map;

    return 0;
}
