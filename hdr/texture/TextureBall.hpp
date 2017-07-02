#ifndef TEXTBALL_HPP
#define TEXTBALL_HPP

#include <cmath>
#include "Texture.hpp"


class TextureBall : public Texture
{
public:
	TextureBall() {};

	TextureBall(const sf::Color &color, const sf::Vector2f &center, const uint rayon) :
	m_rayon(rayon),
	m_center(center),
	m_color(color)
	{
		m_circle = sf::CircleShape(m_rayon);
		m_circle.setOrigin(m_rayon, m_rayon);
		m_circle.setFillColor(m_color);

		update();
	}

	TextureBall &operator=( const TextureBall &copy)
	{
		m_rayon = copy.m_rayon;
		m_center = copy.m_center;
		m_color = copy.m_color;

		m_circle = sf::CircleShape(m_rayon);
		m_circle.setOrigin(m_rayon, m_rayon);
		m_circle.setFillColor(m_color);

		update();
		return *this;
	}

	void setCenter(const sf::Vector2f &center)
	{
		m_center = center;
		update();
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		target.draw(m_circle, states);
	}

	void update()
	{
		m_circle.setPosition(m_center);
	}

	uint m_rayon;
	sf::Vector2f m_center;
	sf::Color m_color;

	sf::CircleShape m_circle;
};

#endif