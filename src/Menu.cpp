#include "../hdr/Menu.hpp"
#include "../hdr/Moteur2D.hpp"

using namespace std;
using namespace sf;

Menu::Menu()
: m_menuNo(0)
, m_ball(Color::Green, Vector2f(W_WINDOW/2, H_WINDOW/2), 4)
, m_robot1(Color::Red)
, m_robot2(Color::Blue)
{
	v_options.push_back(0);

	m_ball.setAngle( (rand()%360)/360.0 * PI);
	m_ball.setSpeed(500);
}

int Menu::getNumberOptions()
{
	switch(m_menuNo)
	{
		case MENU_END:
			return 1;

		case MENU_PRINCIPAL:
			return  3;

		case MENU_OPTION:
			return 1;

		case MENU_SELECTION1:
			return 4;

		case MENU_SELECTION2:
			return 5;
	}
	
	return -1;
}

void Menu::ending(const string winner, const Color color, const int s1, const int s2)
{
	m_menuNo = MENU_END;
	m_textureMenuEnd.setWinnerName(winner);
	m_textureMenuEnd.setWinnerColor(color);
	m_textureMenuEnd.setScore(s1, s2);
}

void Menu::nextSelection()
{
	v_options.back() = (v_options.back() + 1 > getNumberOptions() - 1)? 0 : v_options.back() + 1;

	if(m_menuNo == MENU_SELECTION2 && m_textureMenuSelection.selectedByJ1( v_options.back()))
		nextSelection();
}

void Menu::prevSelection()
{
	v_options.back() = (v_options.back() - 1 < 0)? getNumberOptions() - 1 : v_options.back() - 1;

	if(m_menuNo == MENU_SELECTION2 && m_textureMenuSelection.selectedByJ1( v_options.back()))
		prevSelection();
}

int Menu::prevMenu()
{
	switch(m_menuNo)
	{
		case MENU_END:
			return OPTION_QUIT;
			break;

		case MENU_PRINCIPAL:
			return OPTION_QUIT;
			break;

		case MENU_OPTION:
			m_menuNo = MENU_PRINCIPAL;
			break;

		case MENU_SELECTION1:
			m_menuNo = MENU_PRINCIPAL;
			break;

		case MENU_SELECTION2:
			m_menuNo = MENU_SELECTION1;

		default: break;
	}
	
	v_options.pop_back();

	return 1;
}

int Menu::nextMenu()
{
	switch(m_menuNo)
	{
		case MENU_END:
			return OPTION_QUIT;

		case MENU_PRINCIPAL:
			switch(v_options.back())
			{
				case 0:
					m_menuNo = MENU_SELECTION1;
					break;

				case 1:
					m_menuNo = MENU_OPTION;
					break;

				case 2:
					return OPTION_QUIT;
					break;
				default: break;
			}
			break;

		case MENU_OPTION:
			switch(v_options.back())
			{
				case 0:
					return prevMenu();
					break;

				default: break;
			}
			break;

		case MENU_SELECTION1:
			m_menuNo = MENU_SELECTION2;
			break;

		case MENU_SELECTION2:
			return OPTION_GAME;
			break;

		default: break;
	}

	v_options.push_back(0);

	if(m_menuNo == MENU_SELECTION2 && m_textureMenuSelection.selectedByJ1( v_options.back()))
		nextSelection();

	return 1;
}

void Menu::update(const float dt)
{
	switch(m_menuNo)
	{
		case MENU_END:
			break;

		case MENU_PRINCIPAL:
			m_textureMenuPrincipal.updateSelection(v_options.back());

			break;

		case MENU_OPTION:
			m_textureMenuOption.updateSelection(v_options.back());

			break;

		case MENU_SELECTION1:
			m_textureMenuSelection.updateSelection(0, v_options.back());

			break;

		case MENU_SELECTION2:
			m_textureMenuSelection.updateSelection(1, v_options.back());

			break;

		default: return;
	}

	m_robot1.setAngle(atan2(m_ball.getY() - m_robot1.getY(), m_ball.getX() - m_robot1.getX()));
	m_robot2.setAngle(atan2(m_ball.getY() - m_robot2.getY(), m_ball.getX() - m_robot2.getX()));
	m_ball.update(dt);
	m_ball.setSpeed(500);
	Moteur2D::collision(&m_robot1, &m_ball, dt);
	Moteur2D::collision(&m_robot2, &m_ball, dt);
	Moteur2D::collisionBorder(&m_ball, Vector2f(W_WINDOW - 4 * (FONT_SIZE + 5), H_WINDOW - 4 * (FONT_SIZE + 5)));
}

void Menu::draw(RenderTarget& target, RenderStates states) const 
{
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(m_robot1, states);
	target.draw(m_robot2, states);
	target.draw(m_ball, states);

	switch(m_menuNo)
	{
		case MENU_END:
			target.draw(m_textureMenuEnd, states);
			break;

		case MENU_PRINCIPAL:
			target.draw(m_textureMenuPrincipal, states);
			break;

		case MENU_OPTION:
			target.draw(m_textureMenuOption, states);
			break;

		case MENU_SELECTION1:
			target.draw(m_textureMenuSelection, states);

		case MENU_SELECTION2:
			target.draw(m_textureMenuSelection, states);

		default: break;
	}
}