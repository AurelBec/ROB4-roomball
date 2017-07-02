#ifndef TEXTTEXT_HPP
#define TEXTTEXT_HPP

#include "Texture.hpp"


class TextureText : public Texture
{
public:
	TextureText(){};

	TextureText(const sf::Color color, const std::string str, const uint font_size, const float x = -1.0f, const float y = -1.0f):
	m_font_size(font_size),
	m_str(str),
	m_color(color),
	m_pos(sf::Vector2f(x, y))
	{
		assert(m_font.loadFromFile("fonts/8-bit.ttf"));
		
		m_text.setFont(m_font);
		m_text.setCharacterSize(m_font_size);
		m_text.setColor(m_color);
		
		update();
	}

	TextureText &operator=(const TextureText &copy)
	{
		assert(m_font.loadFromFile("fonts/8-bit.ttf"));
		m_font_size = copy.m_font_size;
		m_str = copy.m_str;
		m_color = copy.m_color;
		m_pos = copy.m_pos;
		
		m_text.setFont(m_font);
		m_text.setCharacterSize(m_font_size);
		m_text.setColor(m_color);
		
		update();
		return *this;
	}

	void setPosition(const sf::Vector2f pos)
	{
		if(pos.x != -1.0f)
			m_pos.x = pos.x + m_text.getLocalBounds().width/2;
		if(pos.y != -1.0f)
			m_pos.y = pos.y;
		
		update();
	}

	void setStr( const std::string str)
	{
		m_str = str;
		update();
	}

	void setColor( const sf::Color color)
	{
		m_color = color;
		update();
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		target.draw(m_text, states);
	}

	void update()
	{
		m_text.setString(m_str);
		m_text.setOrigin(m_text.getLocalBounds().left + m_text.getLocalBounds().width/2, m_text.getLocalBounds().top + m_text.getLocalBounds().height/2);
		m_text.setPosition(m_pos);
		m_text.setColor(m_color);
	}

	uint m_font_size;
	std::string m_str;
	sf::Color m_color;
	sf::Vector2f m_pos;

	sf::Font m_font;
	sf::Text m_text;
};

#endif