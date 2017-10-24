#include "Panel.h"

Panel::Panel()
{

}
Panel::Panel(float width, float height) : m_width(width), m_height(height)
{
    sf::Vector2f tmp = sf::Vector2f(m_width, m_height);
    m_panel.setSize(tmp);
    m_panel.setOutlineThickness(1);
    m_panel.setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
}
void Panel::setPosition(float x, float y)
{
    m_panel.setPosition(x, y);
}
void Panel::setDisplayedObject(Point2D* object)
{
    if(object->getFill()==empty)           m_panel.setFillColor(sf::Color(0, 0, 0, 0));
    if(object->getFill()==obstacle)        m_panel.setFillColor(sf::Color(102, 102, 0));
    if(object->getFill()==food)            m_panel.setFillColor(sf::Color(255, 128, 0));
    if(object->getFill()==blackAnthill)    m_panel.setFillColor(sf::Color(0, 0, 0));
    if(object->getFill()==redAnthill)      m_panel.setFillColor(sf::Color(153, 0, 0));
    if(object->getFill()==blackWorkerAnt)  m_panel.setFillColor(sf::Color(128, 128, 128));
    if(object->getFill()==blackSoliderAnt) m_panel.setFillColor(sf::Color(64, 64, 64));
    if(object->getFill()==redAnt)          m_panel.setFillColor(sf::Color(255, 0, 0));

    if(object->getFill()==empty)
        m_panel.setOutlineColor(sf::Color(153, 0, 153, 2*object->getScentLevel()));
    else
        m_panel.setOutlineColor(sf::Color(0, 0, 0));
}
void Panel::display(sf::RenderWindow &window)
{
    window.draw(m_panel);
}

Panel::~Panel()
{
    //dtor
}
