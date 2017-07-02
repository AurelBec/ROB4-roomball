#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "define.h"
#include <SFML/Graphics.hpp>


class Element : public sf::Drawable, public sf::Transformable 
{
public:
	Element(const sf::Color color, const sf::Vector2f center, const float mass = 0);
	virtual ~Element() {};

	int 	getX()	const;
	int 	getY() 	const;
	float 	getMass() 	const; 

	virtual void 	update(const float dt) = 0;
	virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	const float 	m_mass;
	sf::Color 		m_color;
	sf::Vector2f 	m_center;

private:

};

typedef typename std::vector<Element*> V_ELEMENT;
typedef typename V_ELEMENT::const_iterator IT_ELEMENT;

#endif