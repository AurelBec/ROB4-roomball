#ifndef MOTEUR2D_HPP
#define MOTEUR2D_HPP

#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Settings.hpp"
#include "Game.hpp"
#include "Robots.hpp"
#include "Goal.hpp"
#include "Ball.hpp"
#include "Menu.hpp"
#include "Bonus.hpp"


enum State {QUIT = -1, IN_GAME = 0, IN_MENU = 1};


class Moteur2D
{
public :
	Moteur2D(Settings &settings);
	Moteur2D& operator=(const Moteur2D &copy);
	~Moteur2D();

	static 	void	collision(Robot *robot1, Robot *robot2, const float dt);
	static 	void	collision(Robot *robot, Ball *ball, const float dt);
	static 	void 	collision(Robot *robot, Bonus *bonus, const float dt);
	//static 	int 	collision(Ball *ball, Goal *goal);
	static 	void 	collisionBorder(Ball *ballon, const sf::Vector2f &dim);


	void run();

private :
	int 				m_state;
	Game 				m_game;
	Menu 				m_menu;
	Settings			m_settings;
	sf::Clock 			m_clock;
	sf::RenderWindow 	m_window;

	void 	updateGame();
	void 	updateMenu();
};

#endif