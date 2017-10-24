#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

#include "Point2D.h"
#include "Panel.h"

class Gui
{
    public:
        Gui(sf::RenderWindow &widnow, int map_width, int map_height);
        virtual ~Gui();

        void display();
        void setPanels(Point2D*** point_map);

    protected:

    private:
        sf::RenderWindow &m_window;
        int m_map_width, m_map_height;
        float m_panel_width, m_panel_height;

        Panel** m_panel_map;
};

#endif // GUI_H
