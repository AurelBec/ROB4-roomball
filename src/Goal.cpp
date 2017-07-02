#include "../hdr/Goal.hpp"

using namespace sf;

// CONSTRUCTOR
/////////////////////////
Goal::Goal(const Color color, const uint num, const Vector2f center, const Vector2f dim) 
: m_color(color)
, m_center(center)
, m_dim(dim)
, m_texture(m_color, m_center, m_dim, 4)
, m_numPlayer(num)
{
}

// DESTRUCTOR
/////////////////////////
Goal::~Goal()
{
}

// SETTERS
/////////////////////////
void
Goal::setColor(const Color color)
{
	m_color = color;
	m_texture.setColor(color);
}


// GETTERS
/////////////////////////
float	Goal::getW		() const { return m_dim.x;}	
float	Goal::getH		() const { return m_dim.y;}
float	Goal::getX		() const { return m_center.x - m_dim.x/2.0f;}
float	Goal::getY		() const { return m_center.y - m_dim.y/2.0f;}
uint	Goal::getNum	() const { return m_numPlayer;}

// OTHERS METHODS
/////////////////////////
void 
Goal::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(m_texture, states);
}
