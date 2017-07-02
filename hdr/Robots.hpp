#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "define.h"
#include "texture/TextureRobot.hpp"


class Robot : public sf::Drawable, public sf::Transformable 
{
public:
	Robot(const sf::Color c, const uint num, const uint radius);
	virtual ~Robot() {};

	float	getX()					const;
	float	getY()					const;
	uint	getNum()				const;
	float	getMass()				const;
	uint	getScore()				const;
	float	getSpeed() 				const;
	float	getAngle()				const;
	uint	getRadius()				const;
	bool	isControlled() 			const;
	uint	getBorder(const int i)	const; 
	
	void	addPoint();
	void	setTexture();
	void	setX(const float x);
	void	setY(const float y);
	void	setRadius(const int rayon);
	void	setAngle(const float angle);
	void	setScore(const int score);
	void	setSpeed(const float speed);
	void	setColor(const sf::Color color);
	void	setControlled(const bool state);

	void 	backPreviousPos(const float dt);
	void 	moveRandom(const float dt);
	
	virtual void update(const int action, const float dt) = 0;
	void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Color 			m_color;
	TextureRobot 		m_texture;
	sf::Vector2f 		m_center;
	const uint 			m_playerNo;
	const float 		m_mass;
	bool 				m_isControlled;
	uint				m_score;
	uint	 			m_radius;
	uint 				m_border[2];
	float 				m_angle;
	float 				m_speed;
};


typedef typename std::vector<Robot*> V_ROBOT;
typedef typename V_ROBOT::const_iterator IT_ROBOT;


class RobotAtk : public Robot
{
private:

public:
	RobotAtk(const sf::Color c, const uint num);
	~RobotAtk() {};

	void update(const int action, const float dt);
};


class RobotDef : public Robot
{
private:

public:
	RobotDef(const sf::Color c, const uint num);
	~RobotDef() {};

	void update(const int action, const float dt);
};


class RobotMenu : public Robot
{
private:
	int m_direction;

public:
	RobotMenu(const sf::Color color)
	: Robot(color, 0, 15)
	, m_direction(0)
	{
		int x = rand()%(W_WINDOW - 2*(2*FONT_SIZE + 30)) + (2*FONT_SIZE + 30); 
		int y = rand()%(H_WINDOW - 2*(2*FONT_SIZE + 30)) + (2*FONT_SIZE + 30);
		m_center = sf::Vector2f(x, y);
		m_texture = TextureRobot(m_color, m_center, m_angle, m_radius);
	}

	void update( const int action, const float dt) 
	{ 
		(void) action; 
		(void) dt;
		m_texture.setPosture(m_center, m_angle);
	}
};


#endif