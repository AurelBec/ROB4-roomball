#ifndef BONUS_HPP
#define BONUS_HPP 

#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "define.h"
#include "texture/TextureParticle.hpp"
#include "texture/TextureBonus.hpp"
#include "Robots.hpp"
#include "Element.hpp"

class Bonus: public Element
{
protected:
	int m_rayon;
	sf::Time m_lifetime;
	textureBonus m_textureBonus;
	TextureParticleSystem m_textureParticles;

public:
	Bonus(const sf::Color color, const sf::Vector2f center, int lifetime);
	virtual ~Bonus(){}
	sf::Time getLifetime() const {return m_lifetime;}
	int getRadius() const {return m_rayon;}

	virtual void effect(Robot *rob) = 0;

	virtual void update(const float dt) {(void) dt;}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

 class BonusPoint: public Bonus
 {
 public:

 	BonusPoint(const int dim_x, const int dim_y);
 	~BonusPoint();
 	void effect(Robot *robot)
 	{
 		//rob->setRadius(rob->getRadius() + 5);
 		robot->addPoint();
 		m_lifetime = sf::seconds(0);
 	}
 	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(const float dt);
 };

#endif