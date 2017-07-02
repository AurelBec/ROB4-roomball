#include "../hdr/Element.hpp"

using namespace sf;

// CONSTRUCTOR
/////////////////////////
Element::Element(const Color color, const Vector2f center, const float mass)
: m_mass(mass)
, m_color(color)
, m_center(center)
{
}

// DESTRUCTOR
/////////////////////////

// SETTERS
/////////////////////////


// GETTERS
/////////////////////////
int 	Element::getX	() const { return m_center.x;}
int 	Element::getY	() const { return m_center.y;}
float 	Element::getMass() const { return m_mass;}

// OTHERS METHODS
/////////////////////////
