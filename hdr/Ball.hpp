#ifndef BALL_HPP
#define BALL_HPP

#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "define.h"
#include "Element.hpp"
#include "texture/TextureParticle.hpp"
#include "texture/TextureBall.hpp"


class Ball : public Element
{
public:
	Ball(const sf::Color color, const sf::Vector2f center, const uint r);
	~Ball();

	uint 	getRadius()	const;
	float 	getAngle() 	const;
	float 	getSpeed() 	const;

	void 	setX		(const float x);
	void 	setY		(const float y);
	void 	setAngle	(const float angle);
	void 	setSpeed	(const float speed);

	void 	backPreviousPos(const float dt);
	void 	reset();

	void 	update(const float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	uint 	m_radius;
	float 	m_angle;
	float 	m_speed;
	
	TextureParticleSystem 	m_textureParticles;
	TextureBall 			m_textureBall;
};

#endif