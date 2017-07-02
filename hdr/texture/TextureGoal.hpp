#ifndef TEXTGOAL_HPP
#define TEXTGOAL_HPP

#include "Texture.hpp"


class TextureGoal : public Texture
{
public:
	TextureGoal() {};

	TextureGoal(const sf::Color &color, const sf::Vector2f &center, const sf::Vector2f &dim, const int thickness) 
	: m_thickness(thickness)
	, m_color(color)
	, m_center(center)
	, m_dim(dim)
	{
		for( int i = 0; i < 4; ++i)
			m_border[i] = sf::VertexArray(sf::Quads, 4);

		update();
	}

	TextureGoal &operator=(const TextureGoal &copy)
	{
		m_thickness = copy.m_thickness;
		m_color = copy.m_color;
		m_center = copy.m_center;
		m_dim = copy.m_dim;

		for( int i = 0; i < 4; ++i)
			m_border[i] = sf::VertexArray(sf::Quads, 4);

		update();

		return *this;
	}



	void setCenter(const sf::Vector2f &center)
	{
		m_center = center;
		update();
	}

	void setDim(const sf::Vector2f &dim)
	{
		m_dim = dim;
		update();
	}

	void setColor(const sf::Color &color)
	{
		m_color = color;
		update();
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		for( int i = 0; i < 4; ++i)
			target.draw(m_border[i], states);
	}

	void update()
	{
		int x = m_center.x - m_dim.x / 2,
			y = m_center.y - m_dim.y / 2,
			w = m_dim.x,
			h = m_dim.y;

		for( int i = 0; i < 4; ++i)
		{
			m_border[i][0].position = sf::Vector2f(x + (w-m_thickness)*(i==1), y + (h-m_thickness)*(i==2));
			m_border[i][1].position = sf::Vector2f(x + w - (w-m_thickness)*(i==3), y + (h-m_thickness)*(i==2));
			m_border[i][2].position = sf::Vector2f(x + w - (w-m_thickness)*(i==3), y + h - (h-m_thickness)*(i==0));
			m_border[i][3].position = sf::Vector2f(x + (w-m_thickness)*(i==1), y + h - (h-m_thickness)*(i==0));

			for (int j = 0; j < 4; ++j)
				m_border[i][j].color = m_color;
		}
	}

	int m_thickness;
	sf::Color m_color;
	sf::Vector2f m_center;
	sf::Vector2f m_dim;
	
	sf::VertexArray m_border[4];
};

#endif