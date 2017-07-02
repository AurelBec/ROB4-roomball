#ifndef FIELD_HPP
#define FIELD_HPP

#include <assert.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "texture/TextureField.hpp"
#include "Robots.hpp"
#include "Goal.hpp"
#include "Ball.hpp"
#include "Bonus.hpp"

class Field : public sf::Drawable, public sf::Transformable 
{
public:
	Field();
	~Field();

	void 	addRobot(const std::vector<Robot*> *v_robot);
	void	setColor(const int id, const sf::Color color);

	void 	update(const float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	const sf::Vector2f 		m_dim;
	const sf::Vector2f 		m_center;

	std::vector<Element*> 	m_elements;
	std::vector<Robot*> 	m_robots;
	std::vector<Goal*>		m_goals;

	TextureField	 		m_texture;

	void 	checkCollisionBorder(Robot *robot);
	void 	checkCollisionBorder(Ball *ball);
	void 	checkGoal();
};

#endif