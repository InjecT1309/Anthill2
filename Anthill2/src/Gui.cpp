#include "Gui.h"

Gui::Gui(sf::RenderWindow &window, int map_width, int map_height) : m_map_width(map_width), m_map_height(map_height),
            m_window(window), m_panel_width(800/m_map_width), m_panel_height(600/m_map_height)
{
    m_panel_map = new Panel* [m_map_width];

    for(int x=0; x<m_map_width; x++)
    {
        m_panel_map[x] = new Panel[m_map_height];

        for(int y=0; y<m_map_height; y++)
        {
            m_panel_map[x][y] = Panel(m_panel_width, m_panel_height);
            m_panel_map[x][y].setPosition(x*m_panel_width, y*m_panel_height);
        }
    }
}

void Gui::display()
{
    for(int x=0; x<m_map_width; x++)
    {
        for(int y=0; y<m_map_height; y++)
        {
            m_panel_map[x][y].display(m_window);
        }
    }
}
void Gui::setPanels(Point2D*** point_map)
{
    for(int x=0; x<m_map_width; x++)
    {
        for(int y=0; y<m_map_height; y++)
        {
            m_panel_map[x][y].setDisplayedObject(point_map[x][y]);
        }
    }
}

Gui::~Gui()
{
    for(int x=0; x<m_map_width; x++)
    {
        delete m_panel_map[x];
    }
    delete m_panel_map;
}
