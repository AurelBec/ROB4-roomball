#ifndef TEXTMENUPRINCIPAL_HPP
#define TEXTMENUPRINCIPAL_HPP

#include "../Texture.hpp"
#include "../TextureText.hpp"


class TextureMenuPrincipal : public Texture
{
public:
	TextureMenuPrincipal() :
	m_thickness(H_BORD),
	m_center(W_WINDOW/2, H_WINDOW/2),
	m_dim(W_WINDOW - 4 * (FONT_SIZE + 5) + 2*H_BORD, H_WINDOW - 4 * (FONT_SIZE + 5) + 2*H_BORD)
	{
		
		for( int i = 0; i < 4; ++i)
		{
			float x = m_center.x - m_dim.x / 2, y = m_center.y - m_dim.y / 2, w = m_dim.x, h = m_dim.y;
			
			m_border[i] = sf::VertexArray(sf::Quads, 4);
			m_border[i][0].position = sf::Vector2f(x + (w-m_thickness)*(i==1), y + (h-m_thickness)*(i==2));
			m_border[i][1].position = sf::Vector2f(x + w - (w-m_thickness)*(i==3), y + (h-m_thickness)*(i==2));
			m_border[i][2].position = sf::Vector2f(x + w - (w-m_thickness)*(i==3), y + h - (h-m_thickness)*(i==0));
			m_border[i][3].position = sf::Vector2f(x + (w-m_thickness)*(i==1), y + h - (h-m_thickness)*(i==0));

			for (int j = 0; j < 4; ++j)
				m_border[i][j].color = sf::Color::White;
		}

		m_option[0] = TextureText(sf::Color::White, "ROOMBALL", 3*FONT_SIZE, W_WINDOW/2, H_WINDOW / 4);
		m_option[1] = TextureText(sf::Color::White, "Jouer",    2*FONT_SIZE, W_WINDOW/2, H_WINDOW/4 + 10*FONT_SIZE);
		m_option[2] = TextureText(sf::Color::White, "Options",  2*FONT_SIZE, W_WINDOW/2, H_WINDOW/4 + 15*FONT_SIZE);
		m_option[3] = TextureText(sf::Color::White, "Quitter",  2*FONT_SIZE, W_WINDOW/2, H_WINDOW/4 + 35*FONT_SIZE);
	}

	void updateSelection(const uint option)
	{
		for (int i = 1; i < 4; ++i)
			m_option[i].setColor(sf::Color::White);

		m_option[option + 1].setColor(sf::Color::Red);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		for( int i = 0; i < 4; ++i)
			target.draw(m_border[i], states);

		for (int i = 0; i < 4; ++i)
			target.draw(m_option[i], states);
	}

	int m_thickness;
	sf::Vector2f m_center;
	sf::Vector2f m_dim;
	
	sf::VertexArray m_border[4];
	sf::VertexArray m_selection[4];
	TextureText m_option[4];
};

#endif