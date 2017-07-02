#include "../hdr/Robots.hpp"

using namespace std;
using namespace sf;

// CONSTRUCTOR
/////////////////////////
Robot::Robot(const Color color, const uint playerNo, const uint radius) 
: m_color(color)
, m_playerNo(playerNo)
, m_radius(radius)
, m_mass(10.0f)
, m_isControlled(false)
, m_score(0)
, m_speed(150.0f)
{
}

// DESTRUCTOR
/////////////////////////


// GETTERS
/////////////////////////
float	Robot::getX			() const { return m_center.x;}
float	Robot::getY			() const { return m_center.y;}
uint	Robot::getNum		() const { return m_playerNo;}
float	Robot::getMass		() const { return m_mass;}
uint	Robot::getScore		() const { return m_score;}
float	Robot::getSpeed		() const { return m_speed;}
float	Robot::getAngle		() const { return m_angle;}
uint	Robot::getRadius	() const { return m_radius;}
bool	Robot::isControlled () const { return m_isControlled;}
uint	Robot::getBorder	(const int i) const { return m_border[i];}

// SETTERS
/////////////////////////
void	Robot::setX				(const float x){ m_center.x = x; update(-1 ,0);}
void	Robot::setY				(const float y){ m_center.y = y; update(-1 ,0);}
void	Robot::setRadius		(const int rayon){ m_radius = rayon; m_texture.setRayon(rayon);}
void	Robot::setAngle			(const float angle){ m_angle = angle; 	update(-1 ,0);}
void	Robot::setScore			(const int score){ m_score = score;}
void	Robot::setSpeed			(const float speed){ m_speed = speed;}
void	Robot::setColor			(const Color color){ m_color = color; m_texture.setColor(color);}
void	Robot::setControlled	(const bool state){	m_isControlled = state;	m_texture.setSelectCircle(state);}

// OTHERS METHODS
/////////////////////////
void 
Robot::addPoint()
{ 
	m_score ++;
}

void 
Robot::moveRandom(const float dt)
{
	if(m_isControlled || dt == 0) return;

	m_speed = 100;

	if(rand() % 75 == 0)
		m_angle += (rand()%60 - 30) * PI/180;

	m_center.x += m_speed * dt * cos(m_angle);
	m_center.y += m_speed * dt * sin(m_angle);

	m_texture.setPosture(m_center, m_angle);
}

void 
Robot::backPreviousPos(const float dt)
{
	m_center.x -= dt * m_speed * cos(m_angle);
	m_center.y -= dt * m_speed * sin(m_angle);
	update(-1, 0);
}

void 
Robot::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(m_texture, states);
}

