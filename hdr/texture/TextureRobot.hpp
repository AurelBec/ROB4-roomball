#ifndef TEXTROBOT_HPP
#define TEXTROBOT_HPP

#include <cmath>
#include "Texture.hpp"
#include "../define.h"


class TextureRobot : public Texture
{
public:
	TextureRobot() {};

	TextureRobot(const sf::Color &color, const sf::Vector2f &center, const float angle, const uint rayon)
	: m_rayon(rayon)
	, m_angle(angle)
	, m_center(center)
	, m_color(color)
	{
		m_circle = sf::CircleShape(rayon);
		m_roueGauche = sf::RectangleShape(sf::Vector2f(m_rayon, m_rayon/3));
		m_roueDroite = sf::RectangleShape(sf::Vector2f(m_rayon, m_rayon/3));
		m_line = sf::VertexArray(sf::Lines, 2);

		update();
	}

	TextureRobot &operator=( const TextureRobot &copy)
	{
		m_rayon = copy.m_rayon;
		m_angle = copy.m_angle;
		m_center = copy.m_center;
		m_color = copy.m_color;

		m_circle = sf::CircleShape(m_rayon);
		m_roueGauche = sf::RectangleShape(sf::Vector2f(m_rayon, m_rayon/3));
		m_roueDroite = sf::RectangleShape(sf::Vector2f(m_rayon, m_rayon/3));
		m_line = sf::VertexArray(sf::Lines, 2);

		update();

		return *this;
	}

	void setPosture(const sf::Vector2f &center, const float angle)
	{
		m_center = center;
		m_angle = angle;
		update();
	}

	void setSelectCircle(const bool state)
	{
		m_circle.setOutlineThickness((state)? -3 : 0);
		m_circle.setOutlineColor(sf::Color::White);
		update();
	}

	void setColor(const sf::Color color)
	{
		m_color = color;
		update();
	}
	
	void setRayon(const uint rayon)
	{
		m_circle = sf::CircleShape(rayon);
		m_rayon = rayon;
		update();
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		target.draw(m_roueGauche, states);
		target.draw(m_roueDroite, states);
		target.draw(m_circle, states);
		target.draw(m_line, states);
	}

	void update()
	{
		m_circle.setOrigin(m_rayon, m_rayon);
		m_circle.setPosition(m_center);
		m_circle.setFillColor(m_color);

		m_line[0].position = m_center;
		m_line[0].color = sf::Color::White;
		m_line[1].position = sf::Vector2f(m_center.x + m_rayon*cos(m_angle), m_center.y + m_rayon*sin(m_angle));
		m_line[1].color = sf::Color::White;

		m_roueGauche.setOrigin(m_roueGauche.getSize().x/2, m_roueGauche.getSize().y/2);
		m_roueGauche.setPosition(sf::Vector2f(m_center.x + m_rayon*cos(m_angle+PI/2), m_center.y + (m_rayon-1)*sin(m_angle+PI/2)));
		m_roueGauche.setRotation(m_angle * 180/PI);
		m_roueGauche.setFillColor(sf::Color(120,120,120));
		
		m_roueDroite.setOrigin(m_roueDroite.getSize().x/2, m_roueDroite.getSize().y/2);
		m_roueDroite.setPosition(sf::Vector2f(m_center.x + m_rayon*cos(m_angle-PI/2), m_center.y + (m_rayon-1)*sin(m_angle-PI/2)));
		m_roueDroite.setRotation(m_angle * 180/PI);
		m_roueDroite.setFillColor(sf::Color(120,120,120));
	}

	uint m_rayon;
	float m_angle;
	sf::Vector2f m_center;
	sf::Color m_color;

	sf::CircleShape m_circle;
	sf::RectangleShape m_roueDroite, m_roueGauche;
	sf::VertexArray m_line;
};

#endif