#ifndef GOAL_HPP
#define GOAL_HPP

#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "define.h"
#include "texture/TextureGoal.hpp"


class Goal : public sf::Drawable, public sf::Transformable 
{
public:
	Goal(const sf::Color color, const uint num, const sf::Vector2f center, const sf::Vector2f dim);
	~Goal();

	uint	getNum() const;
	float	getX() const;
	float	getY() const;
	float	getW() const;
	float	getH() const;

	void 	setColor(const sf::Color color);
	
	void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Color 		m_color;
	sf::Vector2f 	m_center;
	sf::Vector2f 	m_dim;
	TextureGoal 	m_texture;
	const uint 		m_numPlayer;
};


typedef typename std::vector<Goal*> V_GOAL;
typedef typename V_GOAL::const_iterator IT_GOAL;


#endif