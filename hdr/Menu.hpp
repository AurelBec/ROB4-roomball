#ifndef MENU_HPP
#define MENU_HPP

#include <assert.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "Ball.hpp"
#include "Robots.hpp"
#include "define.h"
#include "texture/menu/TextureMenuPrincipal.hpp"
#include "texture/menu/TextureMenuOption.hpp"
#include "texture/menu/TextureMenuSelection.hpp"
#include "texture/menu/TextureMenuEnd.hpp"

// menuNo 0 : Menu principal
	//option 0 : Jouer > updateGame()
	//option 1 : Options > ?
	//option 2 : Quitter > m_window.close()

enum MENU {MENU_END = -1, MENU_PRINCIPAL = 0, MENU_OPTION = 1, MENU_SELECTION1 = 2, MENU_SELECTION2 = 3};
enum OPTION {OPTION_QUIT = -1, OPTION_GAME = 0};

class Menu : public sf::Drawable, public sf::Transformable 
{
private:
	int m_menuNo;
	int m_option;

	TextureMenuPrincipal m_textureMenuPrincipal;
	TextureMenuOption m_textureMenuOption;
	TextureMenuSelection m_textureMenuSelection;
	TextureMenuEnd m_textureMenuEnd;

	std::vector<int> v_options;

	Ball m_ball;
	RobotMenu m_robot1 , m_robot2;

public:
	Menu();
	~Menu() {};

	int prevMenu();
	int nextMenu();
	void nextSelection();
	void prevSelection();
	int getNumberOptions();
	void ending(const std::string winner, const sf::Color color, const int s1, const int s2);
	
	void update(const float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getChoix(int idJ)
	{
		return m_textureMenuSelection.getChoix(idJ);
	}
};


#endif