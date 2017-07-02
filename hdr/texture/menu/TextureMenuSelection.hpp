#ifndef TEXTMENUSELECTION_HPP
#define TEXTMENUSELECTION_HPP

#include "../Texture.hpp"
#include "../TextureText.hpp"


class TextureMenuSelection : public Texture
{
public:
	TextureMenuSelection() 
	: m_thickness(H_BORD)
	, m_center(W_WINDOW/2, H_WINDOW/2)
	, m_dim(W_WINDOW - 4 * (FONT_SIZE + 5) + 2*H_BORD, H_WINDOW - 4 * (FONT_SIZE + 5) + 2*H_BORD)
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

		m_option[0] = TextureText(sf::Color::White, "SELECTION", 3*FONT_SIZE, W_WINDOW/2, H_WINDOW/4);
		m_option[1] = TextureText(sf::Color::White, "J1 :", 2*FONT_SIZE, 7*FONT_SIZE, H_WINDOW/4 + 10*FONT_SIZE);
		m_option[2] = TextureText(sf::Color::White, "J2 :", 2*FONT_SIZE, 7*FONT_SIZE-8, H_WINDOW/4 + 15*FONT_SIZE);

		m_option[3] = TextureText(sf::Color::White, "DEF1", FONT_SIZE, 14*FONT_SIZE, H_WINDOW/4 + 10*FONT_SIZE);
		m_option[4] = TextureText(sf::Color::White, "ATK1", FONT_SIZE, 19.5*FONT_SIZE, H_WINDOW/4 + 10*FONT_SIZE);
		m_option[5] = TextureText(sf::Color::White, "ATK2", FONT_SIZE, 25*FONT_SIZE, H_WINDOW/4 + 10*FONT_SIZE);
		m_option[6] = TextureText(sf::Color::White, "DEF2", FONT_SIZE, 30.5*FONT_SIZE, H_WINDOW/4 + 10*FONT_SIZE);
		
		m_option[7] = TextureText(sf::Color::White, "DEF1", FONT_SIZE, 14*FONT_SIZE, H_WINDOW/4 + 15*FONT_SIZE);
		m_option[8] = TextureText(sf::Color::White, "ATK1", FONT_SIZE, 19.5*FONT_SIZE, H_WINDOW/4 + 15*FONT_SIZE);
		m_option[9] = TextureText(sf::Color::White, "ATK2", FONT_SIZE, 25*FONT_SIZE, H_WINDOW/4 + 15*FONT_SIZE);
		m_option[10] = TextureText(sf::Color::White, "DEF2", FONT_SIZE, 30.5*FONT_SIZE, H_WINDOW/4 + 15*FONT_SIZE);
		m_option[11] = TextureText(sf::Color::White, "IA", FONT_SIZE, 35*FONT_SIZE, H_WINDOW/4 + 15*FONT_SIZE);
		
		m_option[12] = TextureText(sf::Color::White, "Retour",  2*FONT_SIZE, W_WINDOW/2, H_WINDOW/4 + 35*FONT_SIZE);
	}

	int getChoix(int idJ) const {return idJ == 0 ? choixJ1 : choixJ2;}

	bool selectedByJ1(int i)
	{
		if(choixJ1 < 2 && i < 2)
			return true;
		if(choixJ1 > 1 && i > 1 && i < 4)
			return true;

		return false;
	}

	void updateSelection(const uint joueur, const uint option)
	{
		if(joueur == 0)
		{
			for(int i = 3; i < 12; ++i)
				m_option[i].setColor(sf::Color::White);

			switch(option)
			{
				case 0:
					m_option[3].setColor(sf::Color::Blue);
					break;
				case 1:
					m_option[4].setColor(sf::Color::Blue);
					break;
				case 2:
					m_option[5].setColor(sf::Color::Red);
					break;
				case 3:
					m_option[6].setColor(sf::Color::Red);
					break;
			}

			choixJ1 = option;
		}
		else
		{
			for(int i = 7; i < 12; ++i)
				m_option[i].setColor( selectedByJ1(i-7) ? sf::Color(40,40,40) : sf::Color::White);

			switch(option)
			{
				case 0:
					m_option[7].setColor(sf::Color::Blue);
					break;
				case 1:
					m_option[8].setColor(sf::Color::Blue);
					break;
				case 2:
					m_option[9].setColor(sf::Color::Red);
					break;
				case 3:
					m_option[10].setColor(sf::Color::Red);
					break;
				case 4:
					m_option[11].setColor(sf::Color::Green);
					break;
			}

			choixJ2 = option;
		}

	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		for( int i = 0; i < 4; ++i)
			target.draw(m_border[i], states);
		
		for (int i = 0; i < 13; ++i)
			target.draw(m_option[i], states);

	}

	int m_thickness;
	sf::Vector2f m_center;
	sf::Vector2f m_dim;
	
	sf::VertexArray m_border[4];
	sf::VertexArray m_selection[4];
	TextureText m_option[13];

	int choixJ1;
	int choixJ2;
};

#endif