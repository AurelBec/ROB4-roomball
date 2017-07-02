#ifndef GAME_HPP
#define GAME_HPP

#include <assert.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "define.h"
#include "texture/TextureText.hpp"
#include "Player.hpp"
#include "Field.hpp"


class Game : public sf::Drawable, public sf::Transformable 
{
public:
	Game();
	~Game();

	void	setOptions(int r1, int r2);
	bool	getFinish() const;
	std::string getWinnerName() const;
	sf::Color getWinnerColor() const;
	int 	getScore(const int i) const;

	void 	updateAction(const sf::Keyboard::Key key, const bool type);
	
	void 	update(const float dt);
	void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	const sf::Vector2f m_dim;
	bool	m_paused;
	float	m_timer;

	Player 	m_J1, m_J2;
	Field 	m_field;
	TextureText m_textureTimer;
};

#endif