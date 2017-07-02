#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include "Texture.hpp"


class TextureField : public Texture
{
public:
	TextureField(sf::Color color, const sf::Vector2f center, const sf::Vector2f dim, const int thickness) :
	m_thickness(thickness),
	m_color(color),
	m_center(center),
	m_dim(dim)
	{
		float x = m_center.x - m_dim.x / 2, y = m_center.y - m_dim.y / 2, w = m_dim.x, h = m_dim.y;

		m_center_circle = sf::CircleShape(30);
		m_center_circle.setOrigin(30, 30);
		m_center_circle.setPosition(m_center);
		m_center_circle.setFillColor(sf::Color::Black);
		m_center_circle.setOutlineThickness(m_thickness/3);
		m_center_circle.setOutlineColor(m_color);

		m_top_circle = sf::CircleShape(dim.y/4);
		m_top_circle.setOrigin(dim.y/4, dim.y/4);
		m_top_circle.setPosition(sf::Vector2f(m_center.x, y));
		m_top_circle.setFillColor(sf::Color::Black);
		m_top_circle.setOutlineThickness(m_thickness/3);
		m_top_circle.setOutlineColor(m_color);

		m_bot_circle = sf::CircleShape(dim.y/4);
		m_bot_circle.setOrigin(dim.y/4, dim.y/4);
		m_bot_circle.setPosition(sf::Vector2f(m_center.x, y+h));
		m_bot_circle.setFillColor(sf::Color::Black);
		m_bot_circle.setOutlineThickness(m_thickness/3);
		m_bot_circle.setOutlineColor(m_color);

		m_top_rect = sf::RectangleShape(sf::Vector2f(m_dim.x, y));
		m_top_rect.setPosition(sf::Vector2f(0,0));
		m_top_rect.setFillColor(sf::Color::Black);
		m_bot_rect = sf::RectangleShape(sf::Vector2f(m_dim.x, y));
		m_bot_rect.setPosition(sf::Vector2f(0,h+y));
		m_bot_rect.setFillColor(sf::Color::Black);

		m_center_line = sf::VertexArray(sf::Quads, 4);
		m_center_line[0].position = sf::Vector2f(x, m_center.y - m_thickness/6);
		m_center_line[1].position = sf::Vector2f(x + w, m_center.y - m_thickness/6);
		m_center_line[2].position = sf::Vector2f(x + w, m_center.y + m_thickness/6);
		m_center_line[3].position = sf::Vector2f(x, m_center.y + m_thickness/6);
		for (int i = 0; i < 4; ++i)
			m_center_line[i].color = m_color;

		m_limitLine[0] = sf::VertexArray(sf::Lines, 2);
		m_limitLine[0][0].position = sf::Vector2f(x, m_center.y + h/4);
		m_limitLine[0][0].color = sf::Color::White;
		m_limitLine[0][1].position = sf::Vector2f(x + w, m_center.y + h/4);
		m_limitLine[0][1].color = sf::Color::White;

		m_limitLine[1] = sf::VertexArray(sf::Lines, 2);
		m_limitLine[1][0].position = sf::Vector2f(x, m_center.y - h/4);
		m_limitLine[1][0].color = sf::Color::White;
		m_limitLine[1][1].position = sf::Vector2f(x + w, m_center.y - h/4);
		m_limitLine[1][1].color = sf::Color::White;
		
		for( int i = 0; i < 4; ++i)
		{
			m_border[i] = sf::VertexArray(sf::Quads, 4);
			m_border[i][0].position = sf::Vector2f(x + (w-m_thickness)*(i==1), y + (h-m_thickness)*(i==2));
			m_border[i][1].position = sf::Vector2f(x + w - (w-m_thickness)*(i==3), y + (h-m_thickness)*(i==2));
			m_border[i][2].position = sf::Vector2f(x + w - (w-m_thickness)*(i==3), y + h - (h-m_thickness)*(i==0));
			m_border[i][3].position = sf::Vector2f(x + (w-m_thickness)*(i==1), y + h - (h-m_thickness)*(i==0));

			for (int j = 0; j < 4; ++j)
				m_border[i][j].color = m_color;
		}
	}

	void setColorLimit(const int i, const sf::Color color)
	{
		m_limitLine[i][0].color = color;
		m_limitLine[i][1].color = color;
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		target.draw(m_limitLine[0], states);
		target.draw(m_limitLine[1], states);

		target.draw(m_top_circle, states);
		target.draw(m_bot_circle, states);
		target.draw(m_top_rect, states);
		target.draw(m_bot_rect, states);

		for( int i = 0; i < 4; ++i)
			target.draw(m_border[i], states);

		target.draw(m_center_line, states);
		target.draw(m_center_circle, states);
	}

	int m_thickness;
	sf::Color m_color;
	sf::Vector2f m_center;
	sf::Vector2f m_dim;
	
	sf::VertexArray m_border[4];
	sf::VertexArray m_limitLine[2];
	sf::VertexArray m_center_line;
	sf::CircleShape m_center_circle;
	sf::CircleShape m_top_circle;
	sf::CircleShape m_bot_circle;
	sf::RectangleShape m_top_rect;
	sf::RectangleShape m_bot_rect;
};

#endif