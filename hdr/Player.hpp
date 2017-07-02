#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <assert.h>
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>

#include "define.h"
#include "texture/TextureText.hpp"
#include "Robots.hpp"


class Player : public sf::Drawable, public sf::Transformable 
{
public :
	Player(const uint numPlayer);
	~Player();

	const std::vector<Robot*> *getEquipe() { return &m_robot;}

	void 		updateAction(const sf::Keyboard::Key key, const bool type);
	void		setControlledRobot(const int id);
	void		setColor(const sf::Color);
	std::string	randomName();

	int 		getScore() const;
	sf::Color 	getColor() const;
	std::string getName() const;
	
	void 	update(const float dt);
	void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;

private :
	static const sf::Keyboard::Key s_control[2][5];
	static const sf::Color s_color[2];
	
	uint 				m_idRobotControlled;
	bool 				m_actionState[4];
	uint				m_score;
	sf::Color 			m_color;
	TextureText 		m_textureNom, m_textureScore;
	std::vector<Robot*> m_robot;
	const uint 			m_numPlayer;
	const std::string 	m_nom;
	
	void 	changeRobot	();
	void 	updateScore	();
	void 	updateRobots(const float dt);
};


typedef typename std::vector<Player*> V_PLAYER;
typedef typename V_PLAYER::const_iterator IT_PLAYER;


#endif