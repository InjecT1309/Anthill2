#ifndef PANEL_H
#define PANEL_H

#include <SFML/Graphics.hpp>

#include "Point2D.h"
#include "Fill.h"

#include <stdlib.h>

class Panel
{
    public:
        Panel();
        Panel(float width, float height);
        virtual ~Panel();

        void setPosition(float x, float y);
        void setDisplayedObject(Point2D* object);
        void display(sf::RenderWindow &window);
    protected:

    private:
        float m_width, m_height;
        sf::RectangleShape m_panel;
};

#endif // PANEL_H
