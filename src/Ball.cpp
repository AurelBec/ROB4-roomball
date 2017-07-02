#include "../hdr/Ball.hpp"

using namespace sf;

// CONSTRUCTOR
/////////////////////////
Ball::Ball(const Color color, const Vector2f center, const uint radius)
: Element(color, center, 1)
, m_radius(radius)
, m_textureParticles(500, m_color)
, m_textureBall(color, center, radius)
{
	reset();
}

// DESTRUCTOR
/////////////////////////
Ball::~Ball()
{
}

// SETTERS
/////////////////////////
void	Ball::setX		(const float x) 	{ m_center.x = x; update(0);}
void	Ball::setY		(const float y) 	{ m_center.y = y; update(0);}
void	Ball::setAngle	(const float angle)	{ m_angle = angle; update(0);}
void	Ball::setSpeed	(const float speed) { m_speed = (speed > 300)? 300 : speed;}

// GETTERS
/////////////////////////
uint	Ball::getRadius	() const { return m_radius;}
float	Ball::getAngle	() const { return m_angle;}
float	Ball::getSpeed	() const { return m_speed;}


// OTHERS METHODS
/////////////////////////
void 
Ball::reset()
{
	m_speed = 0;
	m_angle = 0;
	m_center = Vector2f(W_WINDOW/2, H_WINDOW/2);

	update(0);
}

void 
Ball::update (const float dt)
{
	//float vit = (m_speed * dt > m_rayon-1) ? m_rayon-1 : m_speed * dt;
	m_speed *= 0.9997;
	m_center.x += m_speed * dt * cos(m_angle);
	m_center.y += m_speed * dt * sin(m_angle);

	m_textureParticles.setCenter(m_center);
	m_textureParticles.update(dt);
	m_textureBall.setCenter(m_center);
}

void 
Ball::backPreviousPos (const float dt)
{
	m_center.x -= dt * m_speed * cos(m_angle);
	m_center.y -= dt * m_speed * sin(m_angle);
	
	update(0);
}

void 
Ball::draw (RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(m_textureParticles, states);
	target.draw(m_textureBall, states);
}